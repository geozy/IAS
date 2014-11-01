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

transAct::transAct(syncController* scp,uint32_t ref,task* tp) 
{
    _task=tp;
    _scp=scp;
    _ref=ref;
    _started=std::time(nullptr);
    
    {
        std::lock_guard<std::mutex> lock(_scp->_mx);
        
        _scp->transMap[ref]=this;
        _scp->transQueue.push(ref);
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

