/* 
 * File:   syncController.cpp
 * Author: georgez
 * 
 * Created on 25 October 2014, 17:13
 */

#include <cstdlib>
#include <thread>
#include <chrono>
#include "endPoint.h"
#include "transAct.h"
#include "syncController.h"


std::queue<uint32_t> syncController::transQueue;

std::map<uint32_t,std::weak_ptr<transAct>> syncController::transMap;

syncController::syncController(endPoint* ep){
    
    _active=true;
    _timing=false;
    _complete=false;
    _ep=ep;
    
    std::thread t([this](){
        
        // this must continue to loop back until destruction, when
        //_active is set to false
        while(_active){  
                      
            std::cout << "Timeout Thread: Waiting for release" << std::endl;           
            std::unique_lock<std::mutex> lock(_mut);
            
            // this allows the thread to simply wait until timing services
            // required. main thread must set _timing true and notify one
            while(transQueue.empty()){              
                _cv.wait(lock);               
            }
            
            std::cout << "Timeout Thread: Released" << std::endl;
   
            // keep looping until queue empty
           
            
            while(!isQueueEmpty()){
                auto t=transMap.find(transQueue.front());
                if(t!= transMap.end()){
                    auto pTrans=t->second.lock();
               
                    if(pTrans->isTimedOut()){
                        // The fact that this object is still present, means
                        // that the transaction is still waiting - so fire a timeout
                        notifyCompletion(IAS_RESPONSE_TIMEOUT,pTrans);
                        
                        {
                            std::lock_guard<std::mutex> lock(_mx);
                            
                            // Remove transaction from queue
                            transQueue.pop();

                            // Remove transaction from map
                            transMap.erase(t);
                        }
                    }else{
                        // If the head is valid and not timed out, none are
                        // so lets wait and try again in a second
                        
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                }else{
                    
                    {
                        std::lock_guard<std::mutex> lock(_mx);
                        //most common case, where transaction has been completed
                        // and removed from map... just clean up queue
                        transQueue.pop();
                    }
                }
            
            }
            
            
        } // while _active loop back and wait on queue again
    });
    
    t.detach();
}


syncController::~syncController() {
}

// This method verifies that the transaction has not timed out yet
bool syncController::isSafe(uint32_t transID){
    std::cout << "syncController isSafe: Current token=" << "_currentToken << Transaction Token=" << transID << std::endl;
    return _currentToken==transID;
}



void syncController::runTimer(){
    _complete=false;
    _timing=true;
    _cv.notify_one();
}

// The timer and network result are racing to this function
// First in locks mutex
void syncController::notifyCompletion( int source, std::shared_ptr<transAct> pTrans ){
    
    std::unique_lock<std::mutex> lock(_mutx);
    
    std::cout << "Notify Completion: source=" << source << std::endl;

    // First over the line wins!
    if(!_complete){
        _complete=true;

        switch(source){
            case IAS_RESPONSE_TIMEOUT:
                std::cout << "Notify Completion: TIMEOUT" << std::endl;
                break;

            case IAS_RESPONSE_SUCCESS: 
                std::cout << "Notify Completion: SUCCESS!!" << std::endl;               

                break;
        }
        
        // release before notification
        lock.unlock();
        
        std::cout << "Notify Completion: Release Block" << std::endl;
        
        // release the wait
        _cvm.notify_one();
        
    }   
}

// This method blocks until timeout or result received
void syncController::awaitCompletion(uint32_t ref,std::shared_ptr<task> tp){
      
    _complete=false;
    _timing=true;
    
    // Create the transAct object, this manages timeouts
    auto trans=std::make_shared<transAct>(this,ref,tp);
    
    // release timer thread waiting on conditional variable _timing
    //_cv.notify_one();
    
    std::cout << "awaitCompletion: Start" << std::endl;
    std::unique_lock<std::mutex> lock(_mutw);
    
    // Wait until completion notification
    while(!_complete) _cvm.wait(lock);
    

    std::cout << "awaitCompletion: Done" << std::endl;
}

uint32_t syncController::getTransactionToken(){
    std::lock_guard<std::mutex> lock(_mutb);    
    return _currentToken=_transToken++;
}

void syncController::resetTransactionToken(){
    std::lock_guard<std::mutex> lock(_mutb);
    _currentToken=0;
}

bool syncController::isQueueEmpty(){
    std::lock_guard<std::mutex> lock(_mx);
    return transQueue.empty();
}