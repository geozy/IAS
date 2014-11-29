/* 
 * File:   iasErrors.h
 * Author: georgez
 *
 * Created on 22 October 2014, 16:29
 */

#ifndef IASERRORS_H
#define	IASERRORS_H

#include <boost/system/error_code.hpp>
#include <iostream>
#include <string>

/*
class iasError : public boost::system::error_category
{
public:
    const char *name() const override;
    std::string message(int ev) const override;
    
private:
        
};
*/

enum class Errors : uint32_t {
    IAS_SUCCESS             =0,
    IAS_NOTIMPLEMENTED      =1,
    IAS_UNKNOWN             =255
};

#define MAKE_ERROR_STR( msg ) errorloc(__FILE__,__func__,__LINE__,msg)

#define LOG_ERROR_OUT( msg ) std::cout "Error in " << __FILE__ << " : " << __LINE__ << " : " << __func__ << " : Err Msg = " << msg << std::endl;

std::string errorloc( const char* file,const char* func,int line,const char* msg);

#endif	/* IASERRORS_H */

