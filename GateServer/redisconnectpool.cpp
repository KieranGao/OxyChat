#include "redisconnectpool.h"

RedisConnectPool::RedisConnectPool(size_t pool_size, std::string host, int port, std::string password) :
    pool_size_(pool_size), host_(std::move(host)), port_(port), is_running_(true)   
    {   
        for(int i=1;i<=pool_size;i++) {
            redisContext* context = redisConnect(host.c_str(), port);
            if(context == nullptr or context->err != 0) {
                if(context != nullptr) {
                    redisFree(context);
                }
                continue;
            }

            redisReply* reply = static_cast<redisReply*>(redisCommand(context, "AUTH %s", password.c_str()));
            if(reply->type == REDIS_REPLY_ERROR) {
                freeReplyObject(reply);
                continue;
            }

            freeReplyObject(reply);
            connections_.emplace(context);
        }
    }

RedisConnectPool::~RedisConnectPool() {
    stop();
    std::cerr << "RedisConnectPool Destoryed!" << std::endl;
}

redisPtr RedisConnectPool::getConnection() {
    std::unique_lock<std::mutex> lock(mutex_); 
    cond_.wait(lock, [this](){return !connections_.empty() or !is_running_;});
    if(!is_running_) {
        return redisPtr{nullptr, redisFree};
    }
    auto context = std::move(connections_.front());
    connections_.pop();
    return context;
}

void RedisConnectPool::returnConnection(redisPtr connect) {
    std::lock_guard<std::mutex> lock(mutex_);
    if(is_running_) {
        connections_.push(std::move(connect));
        cond_.notify_one();
    }
}   

void RedisConnectPool::stop() {
    std::lock_guard<std::mutex> lock(mutex_);
    is_running_.store(false);
    cond_.notify_all();
    while(!connections_.empty()) {
        connections_.pop();
    }
}