/* 
 * File:   transAct.h
 * Author: georgez
 *
 * Created on 27 October 2014, 22:26
 */

#ifndef TRANSACT_H
#define	TRANSACT_H

#include <cstdlib>
#include <memory>
#include <ctime>
#include <mutex>

class task;
class syncController;

class transAct {
public:
    
    transAct(syncController*,task* );
    virtual ~transAct();
   
    bool isTimedOut();
    task* getTask(){return _task;}
    uint32_t getRef(){return _ref;}
    
private:
    
    uint32_t getToken();
    
    time_t              _started;
    syncController *    _scp;
    uint32_t            _ref;
    task*               _task;
    
    static std::mutex   _mxTok;
    static uint32_t     _transToken;
};

#endif	/* TRANSACT_H */

