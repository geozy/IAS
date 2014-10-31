/* 
 * File:   eventResponse.h
 * Author: georgez
 *
 * Created on 22 October 2014, 23:12
 */

#ifndef EVENTRESPONSE_H
#define	EVENTRESPONSE_H

class endPoint;

class iasResponse {
public:
    iasResponse(endPoint*);   
    virtual ~iasResponse();
    
private:
    
    endPoint* _pEndpoint;
};

#endif	/* EVENTRESPONSE_H */

