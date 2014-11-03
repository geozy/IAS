/* 
 * File:   iaService.h
 * Author: georgez
 *
 * Created on 23 October 2014, 22:52
 */

#ifndef IASERVICE_H
#define	IASERVICE_H

#include <cstdlib>
#include <string>
class iasServiceBase;

class iaService{
    virtual bool initialise(iasServiceBase*) = 0;
    virtual const char* getServiceName() =0;
    virtual const char* getServiceType() =0;
    virtual void process(const char*,int length)=0;
};


#endif	/* IASERVICE_H */

