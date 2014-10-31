/* 
 * File:   syncController.h
 * Author: georgez
 *
 * Created on 25 October 2014, 17:13
 */

#ifndef SYNCCONTROLLER_H
#define	SYNCCONTROLLER_H

#include <cstdlib>
#include <boost/asio.hpp>
#include <condition_variable>
#include <memory>
#include <mutex>
#include "iasData.h"
#include <queue>
#include <map>

class task;
class endPoint;
class transAct;


class syncController {
    friend class transAct;
    friend class endPoint;
    
 public:   
    static std::queue<uint32_t> transQueue;
    static std::map<uint32_t,std::weak_ptr<transAct>> transMap;
     
    syncController(endPoint* ep);
    virtual ~syncController();
    
    uint32_t getTransactionToken();
    void resetTransactionToken();
    void notifyCompletion( int source ,std::shared_ptr<transAct> pTrans);
    void awaitCompletion(uint32_t ,std::shared_ptr<task>);
    bool isQueueEmpty();
    
    bool isSafe(uint32_t);
    
    
    
private:
    
    void runTimer();
    boost::asio::io_service* _pIOS;
    std::condition_variable _cv;    //manages timer thread activity
    std::mutex              _mut;   //manages timer thread activity
    
    std::mutex              _mutx;  //used to protect completion handler
    std::mutex              _mutb;  //used to protect tokens
    
    std::condition_variable _cvm;   //used to block main thread
    std::mutex              _mutw;  //used to block main thread until done
    std::mutex              _mx;
    
    
    bool                    _active;
    bool                    _timing;
    bool                    _complete;
    
    //boost::asio::deadline_timer _timer;
    endPoint*   _ep;
    uint32_t    _transToken;
    uint32_t    _currentToken;
    task*       _currentTask;
};

#endif	/* SYNCCONTROLLER_H */

