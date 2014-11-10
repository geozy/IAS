/* 
 * File:   iaServiceManager.h
 * Author: georgez
 *
 * Created on 23 October 2014, 23:02
 * 
 * This defines the public interface of the service Manager
 * 
 */

#ifndef IASSERVICEMANAGER_H
#define	IASSERVICEMANAGER_H

#include <cstdlib>
#include <memory>
#include <map>
#include <queue>
#include <mutex>

class iaService;
class iasServer;

class iasServiceManagerBase{
    virtual bool serviceExists(std::string) =0;
    virtual iaService* getService(uint id) =0;
    virtual iaService* getService(std::string) =0;
    virtual uint getServiceID(std::string) =0;
    virtual bool registerService(std::string,iaService* (*)())=0;
};



class iasServiceManager: public iasServiceManagerBase {
    
public:
    iasServiceManager(iasServer*);
    
    bool serviceExists(std::string) override;
    bool registerService(std::string,iaService* (*)()) override;
    iaService* getService(std::string) override; 
    iaService* getService(uint id) override;
    uint getServiceID(std::string) override;
    
protected:
    
    bool isActive(std::string);
    bool createService(std::string);
    
private:
    
    iasServer*                                _pServer;
    std::map<std::string,iaService* (*)()>    _registered_services;  
    std::map<std::string,uint>                _active_services;
    std::queue<uint>                          _available_slots;
    iaService*                                _service_slots[32];
    std::mutex                                _mx;
    
};







#endif	/* IASSERVICEMANAGER_H */

