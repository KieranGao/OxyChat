#ifndef STATUSSERVICEIMPL
#define STATUSSERVICEIMPL

#include "grpcpp/grpcpp.h"
#include "message.grpc.pb.h"
#include "SegmentTree.h"
#include <set>
#include <mutex>
#include <queue>
#include "Global.h"

using grpc::Server;
using grpc::Status;
using grpc::ServerContext;
using grpc::ServerBuilder;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

class ChatServer {
public:
	ChatServer() : host(""), port(""), name(""), id(0) {}
	ChatServer(const ChatServer& cs) : host(cs.host), port(cs.port), name(cs.name), id(cs.id) {}
	ChatServer& operator=(const ChatServer& cs) {
		if(&cs == this) {
			return *this;
		}
		host = cs.host;
		name = cs.name;
		port = cs.port;
		id = cs.id;
		return *this;
	}
	std::string host;
	std::string port;
	std::string name;
	int id;
};

class StatusServiceImpl final : public StatusService::Service {
public:
    StatusServiceImpl();
    Status GetChatServer(ServerContext* context, const GetChatServerReq* req, GetChatServerRsp* resp) override;
    Status Login(ServerContext* context, const LoginReq* req, LoginRsp* resp) override;
private:
    void insertToken(int uid, std::string token);
    ChatServer& getChatServer();
	void returnServer(ChatServer& cs);
    std::unique_ptr<SegmentTree> SegTree_;
    std::unordered_map<std::string, ChatServer> servers_;
    std::unordered_map<int, ChatServer> servers_idx_;
    std::mutex server_mtx_;
    int server_cnt_;
};


#endif /* STATUSSERVICEIMPL */
