/* 
 * File:   endPoint.cpp
 * Author: georgez
 * 
 * Created on 22 October 2014, 16:15
 */

#include "endPoint.h"
#include "iasErrors.h"
#include "iasResponse.h"
#include "task_impl.h"
#include "task.h"
#include "syncController.h"
#include "transAct.h"

auto defaultIACallback=std::make_shared<defaultCB>();


endPoint::endPoint() : 
    _socket(_io_service),
        _sync(this)
{
    buffer_size=1028;
    _is_async=false;
    _is_connected=false;
    _pResponse=new iasResponse(this);
    _pCallback=(iasCallback*)defaultIACallback.get();
    _pHead=(PACKETHEAD_PTR)&_data;
    _transToken=1;
}


endPoint::~endPoint() {
    delete _pResponse;
}

bool endPoint::connect(std::string host,
            std::string port,
                iasCallback* cb){
    
    bool result=true;
    _host=host;
    _port=port;
    
    boost::system::error_code error = boost::asio::error::host_not_found;
    try{
        
        tcp::resolver resolver(_io_service);
        tcp::resolver::query query(host,port);
        tcp::resolver::iterator endpoint_iter = resolver.resolve(query);
        tcp::resolver::iterator end;
     
        while(error && endpoint_iter != end){
            _socket.close();
            _socket.connect(*endpoint_iter++,error);
        }
        
      }catch(std::exception& e){
          
        result=false;
        _error=e.what();
        
    }catch(...){
        
        // catch all
        result=false;
        _error="Unknown";       
    }   
    
    if(error){
        _error=error.message();
    }
    
    if(cb && !error){
        _pCallback=cb;
            
        std::thread t([this](){
                    
            // Listen for responses & request from remote endpoint
            // On separate thread
                    
            do_read();
                                       
            if(!_is_async){
                _is_async=true;
                        
                // Thread will block here in this separate thread
                _io_service.run();
               
                _is_async=false;
            }
        });
        
        t.detach();              
    }
  
    return result;
}


bool endPoint::connect_service(uint servType,std::string service,std::string auth){
    task data;   
    std::strcpy(data.getBuffer(),service.c_str());
    data.getImpl()->setHeader(IAS_PACKETTYPE_REQUEST,servType,service.length());
  
    auto pHead=data.getImpl()->getHeader();
  
    // move data into task buffer
    std::memcpy(data.getBuffer(),service.c_str(),service.length());
    
    transAct trans(&_sync,&data);
    
    // write task
    boost::asio::write(_socket,boost::asio::buffer(pHead,pHead->datasize+sizeof(PACKETHEAD)));
   
    // wait for response or timeout
    _sync.awaitCompletion();
    
    // success / erro in result flag
    return pHead->result == 0;
       
}
     
uint endPoint::write(std::string s){
    boost::asio::write(_socket, boost::asio::buffer(s, s.length()));
    return s.length();
}

uint endPoint::write(const char* data,size_t length){
    boost::asio::write(_socket, boost::asio::buffer(data, length));
    return length;   
}

uint endPoint::writeAwaitResponse(char* data,size_t* plength){
    task t;
    size_t length=*plength;
    
    // move data into task buffer
    std::memcpy(t.getBuffer(),data,length);
    
    // get task header
    auto pHead=t.getImpl()->getHeader();
    
    // setup header
    pHead->length=(uint32_t)length+sizeof(PACKETHEAD);
    pHead->datasize=(uint32_t)length;
    
    // indicate response required
    pHead->resp=1;
    
    //Create the transAct object, this manages timeouts
    transAct trans(&_sync,&t);
    
    // write task
    boost::asio::write(_socket,boost::asio::buffer(pHead,pHead->datasize+sizeof(PACKETHEAD)));
   
    // wait for response or timeout
    _sync.awaitCompletion();
    
    // BUGBUG: No Check on Source buffersize
    std::memcpy(data,t.getBuffer(),pHead->datasize);
    data[pHead->datasize]=0;
    *plength=pHead->datasize;
    
    return true;
}


void endPoint::do_read(){ 
    
    // Clean buffer before next read
    std::memset((void*)&_data,0,1028 + sizeof(PACKETHEAD));
    
    // Wait for input
    _socket.async_read_some(boost::asio::buffer(_pHead, 1028),
        [this](boost::system::error_code ec, std::size_t length)
        { 
          if (!ec)
          {       
              std::cout << "DO Read: Data Read " << length << " bytes" << std::endl;
                  if(_pCallback)
                  {
                      std::cout << "DO Read:Callback is good" << std::endl;
                      
                      // check if a response
                      if(_pHead->resp){
                          
                          //std::cout << "DO Read:Response Signalled" << std::endl;
                          
                          {
                             std::lock_guard<std::mutex> lock(_sync._mx);
                             
                             auto t=syncController::transMap.find(_pHead->id);
                             if(t!= syncController::transMap.end()){
                                 
                                auto pTrans=t->second;
                                task* pTask=pTrans->getTask();
                                
                                auto pImpl=pTask->getImpl();
                                std::memcpy(pTask->getImpl()->getHeader(),_pHead,length);
                                _sync.notifyCompletion(IAS_RESPONSE_SUCCESS,pTrans);
                                
                                // remove the transaction
                                _sync.transMap.erase(t);
                             }else{
                                 //std::cout << "DO Read:Transaction Not Found - timed Out" << std::endl;
                             }  
                             
                          }
                          
                      }else{
                           std::cout << "DO Read:No Response Signalled - Post Data" << std::endl;
                            // onResponse signals data to handle
                            //auto cb=_callback.lock();
                            try{

                                _pCallback->onData(_pResponse,_pHead->buffer); 

                            }catch(...){
                                // The callback must never fail
                                _pCallback->onError(MAKE_ERROR_STR("Exception in onData Handler"));
                            }
                      }
                        
                  }else{
                      //std::cout << "DO Read:BAD CALLBACK" << std::endl;
                      // find a way to report this failure
                      assert(true);
                  }             
             
                // wait for the next data
                do_read();                 
           
          }else{
              std::cout << ec.message() << std::endl;
          }         
    });
}

uint32_t endPoint::getTransactionToken(){
    std::lock_guard<std::mutex> lock(_tokenMutex);    
    return _currentToken=_transToken++;
}

void endPoint::resetTransactionToken(){
    std::lock_guard<std::mutex> lock(_tokenMutex);
    _currentToken=0;
}

