/* 
 * File:   iaServiceDistributor.cpp
 * Author: georgez
 * 
 * Created on 23 October 2014, 23:15
 */

#include "iaServiceDistributor.h"
#include "session.h"

iaServiceDistributor::iaServiceDistributor() {
}

iaServiceDistributor::~iaServiceDistributor() {
}

const char* iaServiceDistributor::getServiceName(){
   return "iasServices:distributor";  
}

const char* iaServiceDistributor::getServiceType(){
    return "distributor" ;  
}


void iaServiceDistributor::process(task* ptask){
     // Do any cleanup with raw data first 
    
    // Then publish to all listeners
    auto i= _listeners.begin();
    while(i != _listeners.end()){
        if(auto ptr=i->lock()){
           ptr->writeToListener(ptask); 
        }else{
            // erase any expired pointers
            i=_listeners.erase(i);
            continue;
        }
    }
    
}