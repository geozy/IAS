/* 
 * File:   iaServiceDistributor.h
 * Author: georgez
 *
 * Created on 23 October 2014, 23:15
 * This class implements an Interactive Service
 * Type: Distributor
 * Accepts publisher input and redistibutes to all listeners
 * 
 * 
 */

#ifndef IASERVICEDISTRIBUTOR_H
#define	IASERVICEDISTRIBUTOR_H

#include "iaService.h"
#include <memory>
#include <set>

class session;

class iaServiceDistributor : public iaService{
public:
    
    iaServiceDistributor();
    virtual ~iaServiceDistributor();
    
    // public iaService methods
    const char* getServiceName() override;
    const char* getServiceType() override;   
    void process(task*) override;

};

#endif	/* IASERVICEDISTRIBUTOR_H */

