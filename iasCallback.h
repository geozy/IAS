/* 
 * File:   iasCallback.h
 * Author: georgez
 *
 * Created on 22 October 2014, 16:23
 */

#ifndef IASCALLBACK_H
#define	IASCALLBACK_H

#include "iasResponse.h"

class iasCallback {
public:
    virtual void onAuthenticate(iasResponse*)=0;
    virtual void onData(iasResponse*,char*)=0; 
    virtual void onConnect(iasResponse*)=0;
    virtual void onDisConnect()=0;
    virtual void onError(std::string error)=0;
    
};

#endif	/* IASCALLBACK_H */

