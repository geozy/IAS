/* 
 * File:   task.cpp
 * Author: georgez
 * 
 * Created on 12 October 2014, 15:06
 */


#include <cstdlib>
#include <iostream>
#include "task.h"
#include "task_impl.h"

task::task(): _pti(new task_impl())
{
    //std::cout << "Task Created" << std::endl;   
}


task::~task() {
    //std::cout << "Task Destructed" << std::endl;
}

void task::clean(){
    return _pti->clean();
}

void task::process(){  
    //std::cout << "WARNING task::process() MUST be overridden" << std::endl;
}

bool task::writeBack(const char* data,size_t length){
    return _pti->writeBack(data,length);
}

char* task::getBuffer(){
    return _pti->getBuffer();
}

size_t task::getBufferSize(){
    return _pti->getBufferSize();
}

int task::getLength(){
    return _pti->getLength();
}
    
tcp::socket* task::getSocket(){
    return _pti->getSocket();
}
    
task_impl* task::getImpl(){
    return _pti.get();
}

