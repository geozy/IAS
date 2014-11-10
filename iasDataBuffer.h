/* 
 * File:   iasDataBuffer.h
 * Author: georgez
 *
 * Created on 10 November 2014, 16:32
 */

#ifndef IASDATABUFFER_H
#define	IASDATABUFFER_H

#include "iasData.h"

class iasDataBuffer {
public:
    iasDataBuffer();
    iasDataBuffer(const iasDataBuffer& orig);
    virtual ~iasDataBuffer();
    
protected:

    size_t getBufferSize();
    char*  getBuffer();
    PACKETHEAD_PTR getHeader();
    
private:
    
    char    _data[IAS_MAX_BUUFER_SIZE+sizeof(PACKETHEAD)];
};

#endif	/* IASDATABUFFER_H */

