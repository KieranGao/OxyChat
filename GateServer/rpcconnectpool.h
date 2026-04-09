#ifndef RPCCONNECTPOOL_H
#define RPCCONNECTPOOL_H

#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "singleton.h"
#include "grpcpp/grpcpp.h"
#include "message.grpc.pb.h"
#include "global.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using message::GetVerifyReq;
using message::GetVerifyRsp;
using message::VerifyService;

class RPCConnectPool {
public:
    RPCConnectPool(size_t pool_size, std::string host, std::string port);
    ~RPCConnectPool();

    std::unique_ptr<VerifyService::Stub> getStub();
    void returnStub(std::unique_ptr<VerifyService::Stub> stub);
    void start();
    void stop();
private:
    std::queue<std::unique_ptr<VerifyService::Stub>> stubs_;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::atomic<bool> is_running_;
    std::string host_;
    std::string port_;
    size_t pool_size_;
};


#endif /* RPCCONNECTPOOL_H */
