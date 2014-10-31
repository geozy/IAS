/* 
 * File:   taskFactory.cpp
 * Author: georgez
 * 
 * Created on 13 October 2014, 16:05
 */

#include <queue>
#include <memory>

#include "taskFactory.h"
#include "task_impl.h"

taskFactory::taskFactory(task* (*mt)() ,int m) {
    _makeTask=mt;
    _max_cache=std::max(m,4);
}


taskFactory::~taskFactory() {
    try{
        while(_task_cache.size() > 0){
           delete  _task_cache.front();
           _task_cache.pop();
        }
        
    }catch(...){
        // Catch All
        std::cout << "Exception Caught ~taskFactory" << std::endl;
    }
}

task* taskFactory::getTask(std::shared_ptr<session> ps){
    task* pTask=nullptr;
    
    // Use mutex to protect queue
    {
        std::unique_lock<std::mutex> lock(this->_queue_mutex);
        
        if(_task_cache.size() > 0){
            pTask=_task_cache.front();
            _task_cache.pop();
        }           
    }
    
    if(pTask==nullptr){
        pTask=_makeTask();
    }
    
    pTask->_pti->clean(ps);
    
    return pTask;
}

void taskFactory::recycleTask(task* tp){
    bool d=true;
    // use mutex to lock queue
    { 
        std::unique_lock<std::mutex> lock(this->_queue_mutex);
        if(_task_cache.size() < (uint)_max_cache){
            _task_cache.push(tp);
            d=false;
        }
     }
     
    if(d){
        delete tp;
    }
    
}

