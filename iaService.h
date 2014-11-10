/* 
 * File:   iaService.h
 * Author: georgez
 *
 * Created on 23 October 2014, 22:52
 */

#ifndef IASERVICE_H
#define	IASERVICE_H

#include <cstdlib>
#include <memory>
#include <string>
#include <set>
#include "iasData.h"

class iasServiceManagerBase;
class session;
class task;

class iaService{
public:
    
    virtual const char* getServiceName() =0;
    virtual const char* getServiceType() =0;
    virtual void process(task*)=0;
    virtual bool connect_service(std::shared_ptr<session>,uint type=IAS_SERVICE_CONSUMER); 
    virtual bool initialise(iasServiceManagerBase*);
    

    
protected:
    
    std::set<std::weak_ptr<session>,std::owner_less<std::weak_ptr<session>>>    _producers;
    std::set<std::weak_ptr<session>,std::owner_less<std::weak_ptr<session>>>    _listeners;

private:
    
    iasServiceManagerBase*              _pManager;
    
};


#endif	/* IASERVICE_H */

