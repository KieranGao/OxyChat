#include "logicsystem.h"
#include "httpconnection.h"
#include "verifygrpcclient.h"
#include "redismanager.h"
// 注册GET请求的URL和对应的回调函数
void LogicSystem::registerGet(std::string url, HttpHandler handler) {
    getHandlers_[url] = handler; // 将URL和对应的回调函数存储到map中
}

void LogicSystem::registerPost(std::string url, HttpHandler handler) {
    postHandlers_[url] = handler; // 将URL和对应的回调函数存储到map中
}


LogicSystem::LogicSystem() {
    registerGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
        beast::ostream(connection->resp_.body()) << "This is a GET response\r\n";
        int cnt = 0;
        for(auto &[key, value] : connection->get_params_) {
            cnt++;
            beast::ostream(connection->resp_.body()) << "param " << cnt << ": " << key << " = " << value << "\r\n";
        }
    });

    registerPost("/get_verify_code", [](std::shared_ptr<HttpConnection> connection) {
        auto body = beast::buffers_to_string(connection->req_.body().data());
        std::cerr << "Received POST data: " << body << std::endl;
        connection->resp_.set(http::field::content_type, "application/json");
        // 解析JSON数据
        Json::Value jsonData;
        Json::Reader reader;
        Json::Value jsonResp;
        // 解析body中的JSON数据，如果解析失败则返回错误信息，成功则jsonData中存储解析后的数据
        bool parse_success = reader.parse(body, jsonData);
        if(!parse_success) {
            std::cerr << "JSON parse error!"<< std::endl;
            jsonResp["error"] = static_cast<int>(ErrorCodes::JSON_PARSE_ERROR);
            auto jsonRespstr = jsonResp.toStyledString();
            beast::ostream(connection->resp_.body()) << jsonRespstr;
            return;            
        }
        auto email = jsonData["email"].asString();
        GetVerifyRsp verifyResp = VerifyGrpcClient::getInstance()->getVerifyCode(email);
        std::cerr << "Parsed email: " << email << std::endl;
        jsonResp["error"] = verifyResp.error();
        jsonResp["email"] = jsonData["email"];
        // 需要转为字符串，因为HTTP响应的body是一个字符串流，不能直接写入Json::Value对象
        auto jsonRespstr = jsonResp.toStyledString();
        beast::ostream(connection->resp_.body()) << jsonRespstr;
        return;
    });

    registerPost("/user_register",[](std::shared_ptr<HttpConnection> connection){
        auto body = beast::buffers_to_string(connection->req_.body().data());
        std::cerr << "Recieved POST data: " << body << std::endl;
        connection->resp_.set(http::field::content_type, "application/json");
        Json::Value jsonData;
        Json::Reader jsonReader;
        Json::Value jsonResp;
        // 解析body中的JSON数据，如果解析失败则返回错误信息，成功则jsonData中存储解析后的数据
        bool parse_success = jsonReader.parse(body, jsonData);
        if(!parse_success) {
            std::cerr << "JSON parse error!"<< std::endl;
            jsonResp["error"] = static_cast<int>(ErrorCodes::JSON_PARSE_ERROR);
            auto jsonRespstr = jsonResp.toStyledString();
            beast::ostream(connection->resp_.body()) << jsonRespstr;
            return;   
        }
        
        std::string verify_code;
        bool valid_code = RedisManager::getInstance()->get(CODE_PREFIX + jsonData["email"].asString(), verify_code);
        if(!valid_code) {
            std::cerr << "Verify code expired" << std::endl;
            jsonResp["error"] = static_cast<int>(ErrorCodes::VERIFY_CODE_EXPIRED);
            std::string jsonstr = jsonResp.toStyledString();
            beast::ostream(connection->resp_.body()) << jsonstr;
            return;
        }
      
        if (verify_code != jsonData["verify_code"].asString()) {
            std::cerr << "Verify code error" << std::endl;
            jsonResp["error"] = static_cast<int>(ErrorCodes::VERIFY_CODE_EXPIRED);
            std::string jsonstr = jsonResp.toStyledString();
            beast::ostream(connection->resp_.body()) << jsonstr;
            return;
        }

        //访问redis查找
        bool user_exist = RedisManager::getInstance()->existskey(jsonData["user"].asString());
        if (user_exist) {
            std::cout << " user exist" << std::endl;
            jsonResp["error"] = static_cast<int>(ErrorCodes::USER_ALREADY_EXISTS);
            std::string jsonstr = jsonResp.toStyledString();
            beast::ostream(connection->resp_.body()) << jsonstr;
            return;
        }

        //否则查找数据库判断用户是否存在
        jsonResp["error"] = 0;
        jsonResp["email"] = jsonData["email"];
        jsonResp ["user"] = jsonData["user"].asString();
        jsonResp["password"] = jsonData["password"].asString();
        jsonResp["confirm"] = jsonData["confirm"].asString();
        jsonResp["verify_code"] = jsonData["verify_code"].asString();
        std::string jsonstr = jsonResp.toStyledString();
        beast::ostream(connection->resp_.body()) << jsonstr;
    });


}

bool LogicSystem::handleGet(std::string url, std::shared_ptr<HttpConnection> connection) {
    if(getHandlers_.find(url) == getHandlers_.end()) return false; // 回调函数未注册
    getHandlers_[url](connection);
    return true;
}
 
bool LogicSystem::handlePost(std::string url, std::shared_ptr<HttpConnection> connection) {
    if(postHandlers_.find(url) == postHandlers_.end()) return false; // 回调函数未注册
    postHandlers_[url](connection);
    return true;
}