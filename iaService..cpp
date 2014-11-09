/* 
 * File:   iaService.cpp
 * Author: georgez
 * 
 * Created on 22 October 2014, 16:15
 */

#include "iaService.h"

bool iaService::initialise(iasServiceManagerBase* pm){  
    _pManager=pm;  
    return true;
}


/**
 * Connect_service
 * Provides opportunity for the service to obtain a pointer back
 * to its connections
 * 
 * @param sp        :shared_ptr to a connecting session
 * @return 
 */
bool connect_service(std::shared_ptr<session> sp){
    
    return true;
}