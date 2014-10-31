/* 
 * File:   threadpool.h
 * Author: georgez
 *
 * Created on 12 October 2014, 17:13
 */

#ifndef THREADPOOL_H
#define	THREADPOOL_H

#include "task.h"
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class iasServer;

class ThreadPool {
public:
    
    ThreadPool(iasServer*,size_t);     
    void  addTask(task* tp);       
    ~ThreadPool();
    
private:
    
    iasServer* pServer_;
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    
    // the task queue
    std::queue< task* > tasks;
    
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
 


#endif	/* THREADPOOL_H */

