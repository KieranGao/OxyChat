#include "StatusServiceImpl.h"
#include "ConfigManager.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "RedisManager.h"
#include <string>
#include <vector>

std::string generate_unique_string()
{
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::string unique_string = boost::uuids::to_string(uuid);
    return unique_string;
}

StatusServiceImpl::StatusServiceImpl()
{
    auto &g_config = ConfigManager::getInstance();
    auto server_list = g_config["ChatServers"]["name"];
    std::vector<std::string> names;
    std::stringstream ss(server_list);
    std::string name;
    while(std::getline(ss,name,',')) names.push_back(name);
    server_cnt_ = names.size();
    // std::cerr << names.size() << std::endl;
    SegTree_ = std::make_unique<SegmentTree>(std::vector<int>(server_cnt_ + 1));
    int idx = 1;
    for(auto &name : names)
    {
        if(g_config[name]["name"].empty()) continue;
        ChatServer server;
        server.port = g_config[name]["port"];
        server.host = g_config[name]["host"];
        server.name = g_config[name]["name"];
        server.id = idx;
        servers_[server.name] = server;
        servers_idx_[idx++] = server;
    }
}

ChatServer& StatusServiceImpl::getChatServer() {
    std::lock_guard<std::mutex> lock(server_mtx_);
    assert(!servers_.empty());
    int minIdx = SegTree_->queryMinidx(1,server_cnt_);
    int minCon = SegTree_->getVal(minIdx);
    SegTree_->updateVal(minIdx, minCon + 1);
    // std::cerr << minIdx << std::endl;
    return servers_idx_[minIdx];
}

void StatusServiceImpl::returnServer(ChatServer& cs) {
    std::lock_guard<std::mutex> lock(server_mtx_);
    SegTree_->updateVal(cs.id, SegTree_->getVal(cs.id) - 1);
}

Status StatusServiceImpl::GetChatServer(ServerContext* context, const GetChatServerReq* req, GetChatServerRsp* resp)
{
    ChatServer& server = getChatServer();
    resp->set_error(static_cast<int>(ErrorCodes::SUCCESS));
    resp->set_host(server.host);
    resp->set_port(server.port);
    resp->set_token(generate_unique_string());
    insertToken(req->uid(), resp->token());
    return Status::OK;
}

Status StatusServiceImpl::Login(ServerContext* context, const LoginReq* request, LoginRsp* resp)
{
	auto uid = request->uid();
	auto token = request->token();

	std::string uid_str = std::to_string(uid);
	std::string token_key = USER_TOKEN_PREFIX + uid_str;
	std::string token_value = "";

	bool success = RedisManager::getInstance().get(token_key, token_value);
	if(!success) {
		resp->set_error(static_cast<int>(ErrorCodes::INVALID_UID));
		return Status::OK;
	}
	
	if(token_value != token) {
		resp->set_error(static_cast<int>(ErrorCodes::INVALID_TOKEN));
		return Status::OK;
	}
	resp->set_error(static_cast<int>(ErrorCodes::SUCCESS));
	resp->set_uid(uid);
	resp->set_token(token);
	return Status::OK;
}

void StatusServiceImpl::insertToken(int uid, std::string token) {
    std::string uid_str = std::to_string(uid);
    std::string token_key = USER_TOKEN_PREFIX + uid_str;
    RedisManager::getInstance().set(token_key, token);
}
