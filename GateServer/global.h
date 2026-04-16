#ifndef GLOBAL_H
#define GLOBAL_H

#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <mutex>
#include <iostream>
#include <json/json.h>

#define CODE_PREFIX "code_"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;   // from <boost/asio/ip/tcp.hpp>

enum class ErrorCodes {
    SUCCESS = 0,
    JSON_PARSE_ERROR = 1001,
    RPC_ERROR = 1002,
    VERIFY_CODE_EXPIRED = 1003,
    USER_ALREADY_EXISTS = 1004,
};

// class ConfigManager;
// extern ConfigManager g_configManager;


// Defer类，类似Go语言的Defer机制，在类对象生命周期结束时调用func回调
class Defer {
public:
    Defer(std::function<void()> func) : func_(func) {}
    ~Defer() {
        func_();
    } 
private:
    std::function<void()> func_;
};


#endif /* GLOBAL_H */
