/* 
 * File:   session_impl.cpp
 * Author: georgez
 * 
 * Created on 23 October 2014, 14:09
 */

#include "session.h"
#include "task.h"
#include "task_impl.h"
#include "iasServer.h"


session::session(tcp::socket& socket,iasServer* serv)
    : socket_(std::move(socket))
  {
       _pServer=serv;
       std::cout << "Session (Default Type) Created" << std::endl;
  }

session::~session(){
       std::cout << "Session Destructed" << std::endl;
   }
   
  void session::start()
  {
        do_read();
  }

  void session::addTask(task* tp){
      _pServer->addTask(tp);
  }
   void session::recycleTask(task* tp){
      _pServer->recycleTask(tp);
  }
  
   task* session::fetchTask(std::shared_ptr<session> ps){
       return _pServer->fetchTask(ps);
   }
   
   
  void session::do_read()
  {
    auto self(shared_from_this());
    
    task* ptask=fetchTask(self);
    
    socket_.async_read_some(boost::asio::buffer(ptask->_pti->_data, max_length),
        [this, self,ptask](boost::system::error_code ec, std::size_t length)
        { 
          bool killTask=true;
          if (!ec)
          {
             ptask->_pti->setLength(length);
             {                 
                    addTask(ptask);
                    killTask=false;
                    
                    do_read();                 
             }
          }else{
              std::cout << ec.message() << std::endl;
          }
          
          // If there is a failure, the task is recycled
          if(killTask){
              recycleTask(ptask);
          }
        });
  }
  
  tcp::socket* session::getSocket(){     
      return &socket_;
  }
  
  void session::writeResponse(task* ptask){
      // prep the header for listeners
      auto header = ptask->getImpl()->getHeader();
      header->resp=1;
      
      // send the data - blocking
      boost::asio::write(socket_,boost::asio::buffer(header,header->length));
  }
  
  void session::writeToListener(task* ptask){
      // prep the header for listeners
      auto header = ptask->getImpl()->getHeader();
      header->resp=0;
      
      // send the data - blocking
      boost::asio::write(socket_,boost::asio::buffer(header,header->length));
  }

  std::shared_ptr<iaService> session::getService(){
      return _pService;
  }



