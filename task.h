/* 
 * File:   Task.h
 * Author: georgez
 *
 * Created on 12 October 2014, 15:06
 */
/*
 A task carries the data received from a session. The Session places all data it receives
 * into a task and adds it to the work queue. A task maintains a weak reference to the
 * session to allow tasks to send a response if necessary. Tasks are pulled off the
 * work queue by a threadpool and each task operates in its own thread until complete.
 * The data will be self identifying and allow the taskManager to identify the correct handler
 * for the data. The server will implement a taskManager.
 */


#ifndef TASK_H
#define	TASK_H

#include <cstdlib>
#include <memory>
#include <boost/asio.hpp>

class task_impl;

using boost::asio::ip::tcp;


class task{
    friend class taskFactory;
    friend class session;
    
public:
    
    task();
    virtual ~task();
    
    char* getBuffer();
    size_t getBufferSize();
    void clean();
    int getLength();
    
    tcp::socket* getSocket();
    task_impl* getImpl();
    
    // Derived classes should implement this
    virtual void process();  
    bool writeBack(const char* data,size_t length);
    
    
    
private:
    
    std::unique_ptr<task_impl> _pti;
};

#endif	/* TASK_H */

