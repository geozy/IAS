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
    
    
}

const char* iaServiceDistributor::getServiceType(){
    return "distributor" ;  
}


void iaServiceDistributor::process(const char* data,int length){
     // Do any cleanup with raw data first
    
    // Then publish to all listeners
    for(auto ps : _listeners){
        ps->writeToListener(data,length);
    }
}