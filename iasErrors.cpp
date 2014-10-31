/* 
 * File:   iasErrors.cpp
 * Author: georgez
 * 
 * Created on 22 October 2014, 16:29
 */

#include "iasErrors.h"
#include "endPoint.h"

const char * iasError::name() const{
    return "Interactivity";
}

std::string iasError::message(int ev) const{
    return "Interactivity Error"; // needs to lookup correct message
}

std::string errorloc( const char* file,const char* func,int line,const char* msg){
    std::ostringstream str;
    str << "Error in " << file << " at " << func << " Line: " << std::to_string(line) << "Error: " << msg;
    return str.str();
}

