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

class iasServiceManagerBase;
class session;

class iaService{
public:
    
    virtual const char* getServiceName() =0;
    virtual const char* getServiceType() =0;
    virtual void process(const char*,int length)=0;
    virtual bool connect_service(std::shared_ptr<session>); 
    virtual bool initialise(iasServiceManagerBase*);
    
private:
    
    std::set<std::weak_ptr<session>>    _producers;
    std::set<std::weak_ptr<session>>    _listeners;
    
    iasServiceManagerBase*              _pManager;
    
};


#endif	/* IASERVICE_H */

