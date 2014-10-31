/* 
 * File:   taskFactory.h
 * Author: georgez
 *
 * Created on 13 October 2014, 16:05
 * 
 * Implements a Task Class Factory, override 
 */

#ifndef TASKFACTORY_H
#define	TASKFACTORY_H
#include <cstdlib>
#include <queue>
#include <mutex>
#include "task.h"

class session;

class taskFactory {
public:
    
    taskFactory(task* (*)(),int);
    virtual ~taskFactory();
    task* getTask(std::shared_ptr<session> ps);
    void recycleTask(task*);
    
private:
    std::function<task* ()> _makeTask;
    std::mutex _queue_mutex;
    std::queue< task* > _task_cache;
    int _max_cache;
};

#endif	/* TASKFACTORY_H */

