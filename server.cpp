/* 
 * File:   server.cpp
 * Author: georgez
 * 
 * Created on 12 October 2014, 16:05
 */

#include "server.h"
#include "iaserver_impl.h"


server::server(boost::asio::io_service& io_service, short port,task* (*makeTask)(),session* (*makeSession)(tcp::socket*,server*))
    : _pias(new iaserver_impl(io_service,port,this,makeTask,makeSession))
  {
       std::cout << "Server Created" << std::endl;    
  }

server::~server(){
       std::cout << "Server Deleted" << std::endl;
}


