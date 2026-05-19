#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>

#include <queue>
#include <mutex>
#include <memory>
#include "Global.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class MainServer;
class LogicSystem;

class Session {

};

#endif /* SESSION_H */
