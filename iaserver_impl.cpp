/* 
 * File:   iaserver_impl.cpp
 * Author: georgez
 * 
 * Created on 23 October 2014, 15:19
 */

#include "iaserver_impl.h"
#include "task_impl.h"
#include "iasData.h"
#include "session.h"


iaserver_impl::iaserver_impl(boost::asio::io_service& io_service, short port, server* ps,task* (*makeTask)())
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
        socket_(io_service),
          _taskFactory(makeTask,8),
            tasks_(this,0)
  {
    
    _pServer=ps;
    do_accept();
  }

iaserver_impl::~iaserver_impl() {
}

void iaserver_impl::do_accept()
  {
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
              //C++ 11 construct Session Object
              //std::shared_ptr<session>(_makeSession(&socket_,_pServer))->start(); 
              std::make_shared<session>(socket,_pServer)->start();
          }

          do_accept();
        });
  }

void iaserver_impl::addTask(task* tp){
      tasks_.addTask(tp);
  }

// just delete for now
void iaserver_impl::recycleTask(task* tp){
    _taskFactory.recycleTask(tp);
}

task* iaserver_impl::fetchTask(std::shared_ptr<session> ps){
   return  _taskFactory.getTask(ps);
}

bool iaserver_impl::preProcess(task_impl* tp){
    PACKETHEAD_PTR pData=tp->getHeader();
    if(pData->ais){/*
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