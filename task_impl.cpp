/* 
 * File:   task_impl.cpp
 * Author: georgez
 * 
 * Created on 23 October 2014, 12:57
 */

#include "task_impl.h"

task_impl::task_impl() {
    std::cout << "Task Impl Created" << std::endl; 
}

task_impl::~task_impl() {
    std::cout << "Task Impl Destroyed" << std::endl;
}

void task_impl::clean(){
    std::cout << "Task Impl Cleaned" << std::endl;
    std::memset(_data,0,max_length);
    length_=0;
}

void task_impl::clean(std::shared_ptr<session> ps){
    _pSession=ps;
    length_=0;
    std::cout << "Task Cleaned" << std::endl;
}


char* task_impl::getBuffer(){
    return ((PACKETHEAD_PTR)_data)->buffer;
}
 
size_t task_impl::getBufferSize(){
    return max_length;
}

int task_impl::getLength(){
    return length_-sizeof(PACKETHEAD);
}

bool task_impl::writeBack(const char* data,size_t length){ 
    getHeader()->resp=1;
    boost:asio:write(*getSocket(),boost::asio::buffer(_data,length+sizeof(PACKETHEAD)));
}

tcp::socket* task_impl::getSocket(){
    if(auto ps=_pSession.lock()){
            return ps->getSocket();
    } 
        
    return nullptr;
}

void task_impl::setLength(int l){
        length_=l;
        _data[l]=0;
    }

PACKETHEAD_PTR task_impl::getHeader(){
    return (PACKETHEAD_PTR)&_data;
}

bool task_impl::preProcess(){
    
    return false;  // indicates further processing, true indicates task complete
}

std::shared_ptr<session> task_impl::getSession(){
    return _pSession.lock();
}

// This method sets up the header for command
void task_impl::setHeader(int type,int command,uint length){
    

    switch(type){
        case IAS_PACKETTYPE_REQUEST:
            setRequestHeader(command,length);
            break;
        case IAS_PACKETTYPE_RESPONSE:
            setResponseHeader(command,length);
            break;
    }
}


void task_impl::setResponseHeader(int command,uint length){
    PACKETHEAD_PTR pHead=getHeader();
    pHead->ais=1;
    pHead->datasize=(uint16_t)length;
    pHead->type=(uint16_t)command;
    
}
void task_impl::setRequestHeader(int command,uint length){
    PACKETHEAD_PTR pHead=getHeader();
    pHead->ais=1;
    pHead->datasize=(uint16_t)length;
    pHead->type=(uint16_t)command;
}