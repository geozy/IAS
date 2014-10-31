/* 
 * File:   iaServiceManager.h
 * Author: georgez
 *
 * Created on 23 October 2014, 23:02
 * 
 * This defines the public interface of the service Manager
 * 
 */

#ifndef IASERVICEMANAGER_H
#define	IASERVICEMANAGER_H

#include <cstdlib>
#include <memory>
class iaService;

class iaServiceManager{
    bool serviceExists(std::string) =0;
    std::shared_ptr<iaService> getService(std::string) =0;
};

#endif	/* IASERVICEMANAGER_H */

