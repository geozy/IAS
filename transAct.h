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

class task;
class syncController;

class transAct : public std::enable_shared_from_this<transAct> {
public:
    
    transAct(syncController*,uint32_t ref,std::shared_ptr<task> );
    virtual ~transAct();
   
    bool isTimedOut();
    std::shared_ptr<task> getTask(){return _task.lock();}
    uint32_t getRef(){return _ref;}
    
private:
    clock_t     _started;
    syncController * _scp;
    uint32_t    _ref;
    std::weak_ptr<task> _task;
};

#endif	/* TRANSACT_H */

