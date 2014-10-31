/* 
 * File:   iaserver_impl.h
 * Author: georgez
 *
 * Created on 23 October 2014, 15:19
 */

#ifndef IASERVER_IMPL_H
#define	IASERVER_IMPL_H

#include <cstdlib>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "threadpool.h"
#include "taskFactory.h"
#include "session.h"

using boost::asio::ip::tcp;

class task;
class task_impl;
class ThreadPool;


class iaserver_impl {
public:
      
  iaserver_impl(boost::asio::io_service& io_service, 
          short port,
          server* ps,
          task* (*makeTask)());
  
  virtual ~iaserver_impl();
  
  void addTask(task* tp); 
  task* fetchTask(std::shared_ptr<session> ps);
  void recycleTask(task* tp);
  bool preProcess(task_impl* tp);
  
private:
    
  void do_accept();
  
  task* (*_makeTask)();

  taskFactory _taskFactory;
  ThreadPool tasks_; 
  tcp::acceptor acceptor_;
  tcp::socket socket_;
  server* _pServer;
  
};

#endif	/* IASERVER_IMPL_H */

