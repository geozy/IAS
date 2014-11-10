/* 
 * File:   iasDataBuffer.cpp
 * Author: georgez
 * 
 * Created on 10 November 2014, 16:32
 */

#include "iasDataBuffer.h"

iasDataBuffer::iasDataBuffer() {
}

iasDataBuffer::iasDataBuffer(const iasDataBuffer& orig) {
}

iasDataBuffer::~iasDataBuffer() {
}


size_t iasDataBuffer::getBufferSize(){
    return IAS_MAX_BUUFER_SIZE;    
}
    
char*  iasDataBuffer::getBuffer(){
     return ((PACKETHEAD_PTR)_data)->buffer;   
}

PACKETHEAD_PTR iasDataBuffer::getHeader(){
     return (PACKETHEAD_PTR)_data;   
}

