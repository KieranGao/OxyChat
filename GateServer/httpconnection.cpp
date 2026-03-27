#include "httpconnection.h"


HttpConnection::HttpConnection(tcp::socket socket)
    : socket_(std::move(socket)) {} 

void HttpConnection::start() {
    auto self = shared_from_this();
    http::async_read(socket_, buffer_, req_, [self](beast::error_code ec, std::size_t
    byte_transferred) {
        try {
            if(ec) {
                std::cout << "read error: " << ec.message() << std::endl;
                return;
            }
            // 这里不需要使用byte_transferred变量，但编译器会警告未使用变量，所以用boost::ignore_unused来避免警告
            boost::ignore_unused(byte_transferred);
            // 否则就处理请求
            self->handleRequest_(std::move(self->req_));
            self->checkDeadline_(); // 检查是否超时
        }
        catch (std::exception& exp) {
            std::cout << "exception is " << exp.what() << std::endl;
        }
    });
}

void HttpConnection::handleRequest_(http::request<http::dynamic_body>&& req) {
    resp_.version(req.version()); // 设置响应的版本
    resp_.keep_alive(false); // 不保持连接，处理完请求就关闭连接

    if(req.method() == http::verb::get) {
        bool ok = LogicSystem::getInstance().handleRequest(req.target(), shared_from_this());
        if (!ok) {
            resp_.result(http::status::not_found);
            resp_.set(http::field::content_type, "text/plain");
            beast::ostream(resp_.body()) << "url not found\r\n";
            makeResponse_(std::move(resp_));
            return;
        }
        resp_.result(http::status::ok);
        resp_.set(http::field::server, "GateServer");
        makeResponse_(std::move(resp_));
        return;
    }
}

void HttpConnection::makeResponse_(http::response<http::dynamic_body>&& resp) {
    auto self = shared_from_this();
    resp_.content_length(resp_.body().size()); // 设置Content-Length头
    http::async_write(socket_, resp_, [self](beast::error_code ec, std::size_t byte_transferred) {
        self->socket_.shutdown(tcp::socket::shutdown_send, ec); // 发送完响应后关闭连接
        self->deadline_.cancel(); // 取消定时器
    });
        
}

void HttpConnection::checkDeadline_() {
    auto self = shared_from_this();
    deadline_.async_wait([self](beast::error_code ec) {
        if (ec) {
            return; // 定时器被取消了，说明连接已经处理完了，不需要关闭连接
        }
        // 否则说明连接超时了，关闭连接
        self->socket_.close(ec);
    });
}