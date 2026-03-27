#ifndef CSERVER_H
#define CSERVER_H

#include "global.h"

class CServer : public std::enable_shared_from_this<CServer>
{
public:
    // iocontext 底层实现了一个事件循环(epoll)，负责监听处理异步操作的事件。
    CServer(boost::asio::io_context& ioc, unsigned short port);
    void start();
    
private:
    tcp::acceptor acceptor_;
    boost::asio::io_context& ioc_;
    tcp::socket socket_;
    
};

#endif /* CSERVER_H */
