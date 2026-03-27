#include "cserver.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short port)
    : acceptor_(ioc, tcp::endpoint(tcp::v4(), port)),
      ioc_(ioc),
      socket_(ioc) {}

void CServer::start()
{    
    // 延长对象生命周期到回调执行时，否则在回调执行时对象可能已经被销毁了
    auto self = shared_from_this();
    acceptor_.async_accept(socket_, [self](beast::error_code ec) {
        try {
            //出错则放弃这个连接，继续监听新链接
            if (ec) {
                self->start();
                return;
            }

            //处理新链接，创建HttpConnection类管理新连接
            // std::make_shared<HttpConnection>(std::move(self->_socket))->start();
            //继续监听
            self->start();
        }
        catch (std::exception& exp) {
            std::cout << "exception is " << exp.what() << std::endl;
            self->start();
        }
    });
}