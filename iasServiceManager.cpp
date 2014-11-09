/* 
 * File:   iasServiceManager.cpp
 * Author: georgez
 * 
 * Created on 27 October 2014, 12:35
 * 
 * serviceManager is responsible for managing the services provided
 * by the application. Applications can create "services" and register
 * them with the Service manager. SM is responsible for the internal
 * starting, publicising and connections to the services. Services will
 * be registered through configuration scripts or internal application
 * logic at startup.
 * 
 * 
 * 
 * 
 * 
 */

#include "iasServiceManager.h"
#include "iaService.h"




iasServiceManager::iasServiceManager(iasServer* ps){ 
    _pServer=ps;
    
}



/**
 * 
 * @param       :  Name of Service being checked
 * @return      :  true if service exists
 */
bool iasServiceManager::serviceExists(std::string){
    
    return false; 
}


/*
 * 
 * @param       : Name of service requested
 * @return      : Pointer to Service or nullptr
 */
iaService* iasServiceManager::getService(std::string sn){
    
    std::lock_guard<std::mutex> lock(_mx);
    auto s=_active_services.find(sn);
    if(s!=_active_services.end()){
        return _service_slots[s->second].get();
    }
    
    
    return nullptr;
}


/**
 * Fast access to service. No checking is done but pointers in the
 * service_slots array ALWAYS point to a valid object, even if it 
 * points to a dummy iaService
 * 
 * 
 * @param id        // Service id
 * @return          // Pointer to iaAervice
 */
iaService* iasServiceManager::getService(uint id){
    return _service_slots[id].get();   
}


/*
 * This function registers a service but does not start it
 * 
 * 
 * @param sname     : Service name
 * @param pMaker    : Factory Function for creating service
 * @return          : true for success, false for failure
 */
bool iasServiceManager::registerService(std::string sname,
                        iaService* (*pMaker)()){
    
    // simply add service & factory method to internal map
    std::lock_guard<std::mutex> lock(_mx);
    _registered_services[sname]=pMaker;  
    return false;
}

/**
 * 
 * @param           : Service Name
 * @return          : success or failure
 */
bool iasServiceManager::createService(std::string sn){
    bool result=false;
    
    // guard the shared resources accessed here
    std::lock_guard<std::mutex> lock(_mx);
    
    // Check if service already active
    if(_active_services.find(sn) == _active_services.end()){
        
        // Get the factory method
        auto s=_registered_services.find(sn);
        if(s!=_registered_services.end()){
                       
            // create the service object
            std::shared_ptr<iaService> pService(s->second());
            
            // Get available slot
            if(!_available_slots.empty()){          
                uint serviceid=_available_slots.front();               
                _available_slots.pop();
                
                // Map Serviceid to service name, entry in this
                // map controls the lifetime of the service
                _active_services[sn]=serviceid;
                
                // Add raw service pointer to service vector
                _service_slots[serviceid]=pService;
                
                // Initialise Service
                result=pService->initialise(this);
                
                
            }else{
                // No Free Slots
            }           
        }else{
            // Service NOT registered
        }
    }else{
        result=true;
    }
    
    return result;
}

/**
 * 
 * @param           : Service Name
 * @return          : success or failure
 */
bool iasServiceManager::isActive(std::string sn){
    std::lock_guard<std::mutex> lock(_mx);
    return _active_services.find(sn) != _active_services.end();
}


uint iasServiceManager::getServiceID(std::string sn){
    
    if(createService(sn)){
        std::lock_guard<std::mutex> lock(_mx);
        auto s =_active_services.find(sn);
        if(s!=_active_services.end()){
            return s->second;
        }
    }
    
    return 0;  
}
