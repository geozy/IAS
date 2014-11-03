/* 
 * File:   transAct.cpp
 * Author: georgez
 * 
 * Created on 27 October 2014, 22:26
 */

#include "transAct.h"
#include "syncController.h"
#include <time.h>
#include <math.h>
#include "task.h"
#include "task_impl.h"

uint32_t    transAct::_transToken=1;
std::mutex  transAct::_mxTok;

transAct::transAct(syncController* scp,task* tp) 
{
    _task=tp;
    _scp=scp;
    _ref=getToken();
    _started=std::time(nullptr);
    
    auto pt=tp->getImpl()->getHeader();
    pt->id=_ref;
    
    {
        std::lock_guard<std::mutex> lock(_scp->_mx);
        
        _scp->transMap[_ref]=this;
        _scp->transQueue.push(_ref);
    }
    
    //std::cout << "TransAct: created id=" << ref << " Notify_One sent" <<std::endl;
    _scp->_cv.notify_one();
}



transAct::~transAct() {
    
}


// checks for timeout of 5 secs
bool transAct::isTimedOut(){
    time_t diff=std::time(nullptr) -_started;
    return diff > 5;  
}


uint32_t transAct::getToken(){
    std::lock_guard<std::mutex> lock(transAct::_mxTok);
    return transAct::_transToken++;
}