/* 
 * File:   threadpool.cpp
 * Author: georgez
 * 
 * Created on 12 October 2014, 17:13
 */

#include <cstdlib>
#include "threadpool.h"
#include "iasServer.h"
#include "iaService.h"
#include "task_impl.h"

// the constructor just launches some amount of workers
ThreadPool::ThreadPool(iasServer* ps, size_t t = 0)
    :   stop(false)
{
    size_t threads= t==0 ? std::max(std::thread::hardware_concurrency(),(unsigned int)4):t;
    pServer_=ps;
    
    std::cout << "ThreadPool Creation with " << threads << std::endl;
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(
            [this]
            {
                for(;;)
                {
                    task* ptask;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                            
                        ptask = this->tasks.front();
                        this->tasks.pop();
                    }

                    // Do the task processing, method is virtual
                    try{
                        //
                        if(!this->pServer_->preProcess(ptask)){  
                            std::cerr << "Threadpool: Process Task" << std::endl;
                            
                            //ptask->process();
                            
                            // we need to target this task to the correct service
                            // get the service reference
                            PACKETHEAD_PTR header=(ptask->getImpl())->getHeader();
                            
                            auto service=pServer_->getService(header->sid);
                            if(service){                      
                                service->process(ptask);
                            }else{
                               std::cerr << "ERROR: Service ID NOT FOUND" << std::endl; 
                            }
                            
                        }
                    }catch(...){
                        std::cerr << "ERROR: Task Process Exception" << std::endl;
                    }
                    
                    // On completion of task, recycle it
                    this->pServer_->recycleTask(ptask);
                }
            }
        );
}


void ThreadPool::addTask(task* tp) {
       
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        // put task on queue
        tasks.push(tp);
    }
    
    condition.notify_one();
    
}

// the destructor joins all threads
ThreadPool::~ThreadPool()
{
    std::cout << "Threadpool Destruction Started" << std::endl;
    
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}
