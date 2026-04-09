#include "rpcconnectpool.h"

RPCConnectPool::RPCConnectPool(size_t pool_size, std::string host, std::string port) 
    : is_running_(true), host_(std::move(host)), port_(std::move(port)), pool_size_(pool_size) 
{
    // 构造函数不启动连接池，调用start()函数后才会创建连接
    for(int i=0;i<pool_size;i++) {
        std::shared_ptr<Channel> channel = grpc::CreateChannel(host_ + ":" + port_, grpc::InsecureChannelCredentials());
        stubs_.emplace(VerifyService::NewStub(channel));
    }
}

RPCConnectPool::~RPCConnectPool() {
    std::lock_guard<std::mutex> lock(mutex_);
    stop();
    while(!stubs_.empty()) {
        stubs_.front().reset();
        stubs_.pop();
    }
    std::cerr << "RPCConnectPool is destroyed" << std::endl;
}

std::unique_ptr<VerifyService::Stub> RPCConnectPool::getStub() {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this](){ return !stubs_.empty() or !is_running_; });
    if(!is_running_) {
        return nullptr; // 连接池已停止，返回空指针
    }
    auto stub = std::move(stubs_.front());
    stubs_.pop();
    return stub;
}

void RPCConnectPool::returnStub(std::unique_ptr<VerifyService::Stub> stub) {
    std::lock_guard<std::mutex> lock(mutex_);
    if(is_running_) {
        stubs_.push(std::move(stub));
        cond_.notify_one();
    }
}

void RPCConnectPool::stop() {
    std::lock_guard<std::mutex> lock(mutex_);
    is_running_ = false;
    cond_.notify_all(); // 唤醒所有等待的线程，让它们退出
}