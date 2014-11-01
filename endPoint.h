/* 
 * File:   endPoint.h
 * Author: georgez
 *
 * Created on 22 October 2014, 16:15
 */

#ifndef ENDPOINT_H
#define	ENDPOINT_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <assert.h>
#include <boost/asio.hpp>
#include "iasCallback.h"
#include "iasData.h"
#include "syncController.h"

class task;

using boost::asio::ip::tcp;

class endPoint {
    friend syncController;
public:
    endPoint();
    virtual ~endPoint();
    
   bool connect(std::string host,
            std::string port,
            std::shared_ptr<iasCallback> cb=nullptr );
   
   bool connect_service(std::string service,std::string auth="");
   
    uint write(std::string );
    uint write(const char*,size_t);
   
    std::string& getError(){return _error;}
    void wait(){
        
    }
    bool sendAwaitResponse(task* ,size_t);
    
protected:
    
    char _data[1028 + sizeof(PACKETHEAD)];
    
private:
    
    
    void do_read();
    
    uint32_t getTransactionToken();
    void resetTransactionToken();
    
    int buffer_size;
    bool _is_async=false;
    bool _is_connected=false;
    boost::asio::io_service _io_service; 
    
    iasResponse* _pResponse;
    std::weak_ptr<iasCallback> _callback;
    std::string _service;
    std::string _port;
    std::string _host;
    std::string _error;
    
    PACKETHEAD_PTR _pHead;
    uint32_t    _transToken;
    uint32_t    _currentToken;
    std::mutex  _tokenMutex;
    
    syncController _sync;
public:
    tcp::socket _socket;

};

#endif	/* ENDPOINT_H */

