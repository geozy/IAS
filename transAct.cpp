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

transAct::transAct(syncController* scp,uint32_t ref,std::shared_ptr<task> tp) : 
    _task(tp)
{
    _scp=scp;
    _ref=ref;
    _started=clock();
    
    {
        std::lock_guard<std::mutex> lock(_scp->_mx);
        
        _scp->transMap[ref]=shared_from_this();
        _scp->transQueue.push(ref);
    }
    
    std::cout << "TransAct: created id=" << ref << " Notify_One sent" <<std::endl;
    _scp->_cv.notify_one();
}



transAct::~transAct() {
    
}

bool transAct::isTimedOut(){
    time_t diff=clock()-_started;
    return std::floor(((float)diff)/CLOCKS_PER_SEC) > 7;
}

