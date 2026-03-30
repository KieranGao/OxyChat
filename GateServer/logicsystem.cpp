#include "logicsystem.h"
#include "httpconnection.h"

// 注册GET请求的URL和对应的回调函数
void LogicSystem::registerGet(std::string url, HttpHandler handler) {
    getHandlers_[url] = handler; // 将URL和对应的回调函数存储到map中
}

LogicSystem::LogicSystem() {
    registerGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
        beast::ostream(connection->resp_.body()) << "This is a GET response\r\n";
    });
}

bool LogicSystem::handleGet(std::string url, std::shared_ptr<HttpConnection> connection) {
    if(getHandlers_.find(url) == getHandlers_.end()) return false; // 回调函数未注册
    getHandlers_[url](connection);
    return true;
}
 