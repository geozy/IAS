/* 
 * File:   task_impl.h
 * Author: georgez
 *
 * Created on 23 October 2014, 12:57
 */

#ifndef TASK_IMPL_H
#define	TASK_IMPL_H

#include <cstdlib>
#include <memory>
#include <boost/asio.hpp>
#include "session.h"
#include "iasData.h"

using boost::asio::ip::tcp;

class task_impl {
    friend class session;
    
public:
    
    task_impl();   
    virtual ~task_impl();
    
    void clean();
    char* getBuffer();
    size_t getBufferSize();
    
    int getLength();
    void setLength(int);
    
    tcp::socket* getSocket();
    bool writeBack(const char* data,size_t length);
    
    bool preProcess();
    void clean(std::shared_ptr<session> ps);
    PACKETHEAD_PTR getHeader(); 
    
    std::shared_ptr<session> getSession();
    
    void setHeader(int type,int command,uint length);
    
private:
 
    void setRequestHeader(int command,uint length);
    void setResponseHeader(int command,uint length);
    
    enum { max_length = 1024 };
    int length_;
    char _data[max_length];
    std::weak_ptr<session> _pSession;

};

#endif	/* TASK_IMPL_H */

