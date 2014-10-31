/* 
 * File:   server.h
 * Author: georgez
 *
 * Copyright (c) 2012-2014 Dataflare Computing Ltd   George Zygmund MSc
 * 
 * 
 * The server object accepts tcp connections on one thread and hands the work 
 * off to a queue of tasks. Each connection is handled for its lifetime by a 
 * session object. Tasks are pulled off the queue my multiple threads in a FIFO
 * manner. Tasks are required to override the "process" method and it is here
 * that they can handle the data associated with the task. Tasks are able to 
 * respond through access to the underlying Session ( and its socket ).
 * 
 * The server object allows for a generic base multi-threaded service to be 
 * quickly implemented. Its behaviour is determined by the underlying session
 * and task objects - both of which can be derived from to instantiate the
 * required behaviours.
 * 
 * Factory functors for both tasks and sessions are passed to the server 
 * constructor. A default create session functor is instantiated if no
 * new class is derived from session.
 * 
 * All tasks are carried out in multiple threads and so as some tasks can take 
 * longer than others no order of tasks can be guaranteed. Where ordered 
 * processing is required, it is the responsibility of the submitting 
 * application to wait for one task to complete before submitting another or 
 * that functionality to be implemented in the application.
 * 
 * 
 * 
 * 
 */

#ifndef SERVER_H
#define	SERVER_H

#include <cstdlib>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class task;
class session;
class iaserver_impl;

class server
{
    friend class session;
    
public:
  server(boost::asio::io_service& io_service, 
          short port,
          task* (*makeTask)(),
          session* (*makeSession)(tcp::socket*,server*)=nullptr);
  
  virtual ~server();
  
private:   
    
    std::unique_ptr<iaserver_impl> _pias; 
};



#endif	/* SERVER_H */

