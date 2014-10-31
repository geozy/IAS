/* 
 * File:   iasServer.cpp
 * Author: georgez
 * 
 * Created on 27 October 2014, 12:35
 */

#include "iasServer.h"
#include "iasData.h"
#include "task_impl.h"

iasServer::iasServer(boost::asio::io_service& io_service, short port, task* (*makeTask)())
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        socket_(io_service),
          _taskFactory(makeTask,8),
            tasks_(this,0)
  {
    std::cout << "iasServer Created" << std::endl;
    do_accept();
  }

iasServer::~iasServer() {
     std::cout << "iasServer Destroyed" << std::endl;
}

void iasServer::do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
              //C++ 11 construct Session Object
              //std::shared_ptr<session>(_makeSession(&socket_,_pServer))->start(); 
              auto sess=std::shared_ptr<session>(new session(socket_,this));
              sess->start();
          }

          do_accept();
        });
  }

void iasServer::addTask(task* tp){
      tasks_.addTask(tp);
  }

// just delete for now
void iasServer::recycleTask(task* tp){
    _taskFactory.recycleTask(tp);
}

task* iasServer::fetchTask(std::shared_ptr<session> ps){
   return  _taskFactory.getTask(ps);
}

bool iasServer::preProcess(task_impl* tp){
    PACKETHEAD_PTR pData=tp->getHeader();
    
    std::cout << "iasServer PreProcess" << std::endl;
    
    if(pData->ais){
        std::cout << "iasServer PreProcess IAS Flag Set" << std::endl;
        
        /*
        // AIS Signal Set, so handle here
        switch(pData->ais){
            case AIS_SERVICE_PRODUCER:
                // producer requesting to set up service
                
                // check authentication
                
                // check service does not already exist
                
                // if does pass back service reference (ref))
                
                // else create service and pass back service reference
                
                
                break;
            case AIS_SERVICE_CONSUMER:
                // consumer requesting service
                
                // check authentication
                
                // check if service exists
                
                // pass this session to the service               
                
                break;
            
            case AIS_SERVICE_DETACH:
                // called when consumer wants to detach from service
                
                break;
                
            case AIS_SERVICE_CLOSE:  
                // called when producer wants to detach from service
                // if there are no other producers, all consumers are
                // notified. Service will remain until all consumer/
                // producers have left.
                
                break;
               
        }
        */ 
        return false;
    }
    return false;
}