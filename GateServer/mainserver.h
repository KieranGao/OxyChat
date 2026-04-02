#ifndef MAINSERVER_H
#define MAINSERVER_H

#include "global.h"
#include "httpconnection.h"

class MainServer : public std::enable_shared_from_this<MainServer>
{
public:
    // iocontext 底层实现了一个事件循环(epoll)，负责监听处理异步操作的事件。
    MainServer(boost::asio::io_context& ioc, unsigned short port);
    void start();
    
private:
    tcp::acceptor acceptor_;
    boost::asio::io_context& ioc_;
    tcp::socket socket_;
    
};

#endif /* MAINSERVER_H */
