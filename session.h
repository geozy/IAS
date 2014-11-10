/* 
 * File:   session_impl.h
 * Author: georgez
 *
 * Created on 23 October 2014, 14:09
 */

#ifndef SESSION_H
#define	SESSION_H

#include <cstdlib>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class iasServer;
class iaService;
class task;

class session : 
    public std::enable_shared_from_this<session> {
     
public:
    
    session(tcp::socket& socket,iasServer* serv);
    virtual ~session();  
    
    tcp::socket* getSocket();
    void start();
    
    void writeToListener(task*);
    
    std::shared_ptr<iaService> getService();
    
private:
       
    void addTask(task* tp);
    task* fetchTask(std::shared_ptr<session> ps);
    void recycleTask(task* tp);
    
    void do_read();
  
    tcp::socket socket_;
    enum { max_length = 1024 };
    //char data_[max_length];
    iasServer* _pServer;
   
    std::shared_ptr<iaService> _pService;
};

#endif	/* SESSION_IMPL_H */

