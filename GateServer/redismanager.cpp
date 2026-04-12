#include "redismanager.h"


RedisManager::RedisManager() {
    this->connect_ = nullptr;
    this->reply_ = nullptr;
}

RedisManager::~RedisManager() {
    close(); // 关闭连接
}

// 连接Redis服务器
bool RedisManager::connect(const std:: string& host, int port) {
    this->connect_ = redisConnect(host.c_str(), port);
    if (this->connect_->err) {
        std::cerr << "Failed to connect to Redis!" << std::endl;
        return false;
    }
    return true;
}

// 获取值，存入value中
bool RedisManager::get(const std::string& key, std::string& value) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "GET %s", key.c_str()));

    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute GET command!" << std::endl;
        // 此时无需释放reply_，因为它是nullptr
        return false;
    }

    if (this->reply_->type == REDIS_REPLY_STRING) {
        value = std::string(this->reply_->str, this->reply_->len);
        freeReplyObject(this->reply_);
        std::cerr << "Executed command [ GET " << key << " ] success ! " << std::endl;
        return true;
    }
    freeReplyObject(this->reply_);
    return false;
}

bool RedisManager::set(const std::string& key, const std::string& value) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "SET %s %s", key.c_str(), value.c_str()));
    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute SET command!" << std::endl;
        return false;
    }
    //如果执行失败则释放连接
    if (!(this->reply_->type == REDIS_REPLY_STATUS and (strcmp(this->reply_->str, "OK") == 0 or strcmp(this->reply_->str, "ok") == 0)))
    {
        std::cerr << "Execute command [ SET " << key << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(this->reply_);     
        return false;
    }
    freeReplyObject(this->reply_);
    std::cerr << "Execut command [ SET " << key << "  " << value << " ] success ! " << std::endl;
    return true;
}

bool RedisManager::auth(const std::string& password) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "AUTH %s", password.c_str()));


    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute AUTH command!" << std::endl;
        return false;
    }

    if (this->reply_ and this->reply_->type == REDIS_REPLY_ERROR) {
        std::cerr << "Failed to authenticate with Redis!" << std::endl;
        freeReplyObject(this->reply_);
        return false;
    }

    freeReplyObject(this->reply_);
    std::cerr << "Authenticated with Redis successfully." << std::endl;
    return true;
}

bool RedisManager::del(const std::string& key) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "DEL %s", key.c_str()));
    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute DEL command!" << std::endl;
        return false;
    }
    if (this->reply_->type != REDIS_REPLY_INTEGER or this->reply_->integer <= 0) {
        std::cerr << "Failed to execute DEL command!" << std::endl;
        freeReplyObject(this->reply_);
        return false;
    }
    freeReplyObject(this->reply_);
    std::cerr << "Executed command [ DEL " << key << " ] success ! " << std::endl;
    return true;
}

bool RedisManager::lpush(const std::string& key, const std::string& value) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "LPUSH %s %s", key.c_str(), value.c_str()));
    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute LPUSH command!" << std::endl;
        return false;
    }
    if (this->reply_->type != REDIS_REPLY_INTEGER or this->reply_->integer <= 0) {
        std::cerr << "Failed to execute LPUSH command!" << std::endl;
        freeReplyObject(this->reply_);
        return false;
    }
    freeReplyObject(this->reply_);
    std::cerr << "Executed command [ LPUSH " << key << "  " << value << " ] success ! " << std::endl;
    return true;
}

bool RedisManager::rpush(const std::string& key, const std::string& value) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "RPUSH %s %s", key.c_str(), value.c_str()));
    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute RPUSH command!" << std::endl;
        return false;
    }
    if (this->reply_->type != REDIS_REPLY_INTEGER or this->reply_->integer <= 0) {
        std::cerr << "Failed to execute RPUSH command!" << std::endl;
        freeReplyObject(this->reply_);
        std::cerr << "Executed command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
        return false;
    }
    freeReplyObject(this->reply_);
    std::cerr << "Executed command [ RPUSH " << key << "  " << value << " ] success ! " << std::endl;
    return true;
}

bool RedisManager::lpop(const std::string& key, std::string& value) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "LPOP %s", key.c_str()));
    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute LPOP command!" << std::endl;
        return false;
    }
    if (this->reply_->type == REDIS_REPLY_STRING) {
        value = std::string(this->reply_->str, this->reply_->len);
        freeReplyObject(this->reply_);
        std::cerr << "Executed command [ LPOP " << key << " ] success ! " << std::endl;
        return true;
    }
    freeReplyObject(this->reply_);
    std::cerr << "Failed to execute LPOP command!" << std::endl;
    return false;
}

bool RedisManager::rpop(const std::string& key, std::string& value) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "RPOP %s", key.c_str()));
    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute RPOP command!" << std::endl;
        return false;
    }
    if (this->reply_->type == REDIS_REPLY_STRING) {
        value = std::string(this->reply_->str, this->reply_->len);
        freeReplyObject(this->reply_);
        std::cerr << "Executed command [ RPOP " << key << " ] success ! " << std::endl;
        return true;
    }
    freeReplyObject(this->reply_);
    std::cerr << "Failed to execute RPOP command!" << std::endl;
    return false;
}

bool RedisManager::hset(const std::string &key, const std::string &field, const std::string &value) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "HSET %s %s %s", key.c_str(), field.c_str(), value.c_str()));
    if (this->reply_ == nullptr or this->reply_->type != REDIS_REPLY_INTEGER ) {
        std::cerr << "Executed command [ HSet " << key << "  " << field <<"  " << value << " ] failure ! " << std::endl;
        freeReplyObject(this->reply_);
        return false;
    }
    std::cerr << "Executed command [ HSet " << key << "  " << field <<"  " << value << " ] success ! " << std::endl;
    freeReplyObject(this->reply_);
    return true;
}
bool RedisManager::hset(const char* key, const char* field, const char* value, size_t valuelen)
{
    const char* argv[4];
    size_t argvlen[4];
    argv[0] = "HSET";
    argvlen[0] = 4;
    argv[1] = key;
    argvlen[1] = strlen(key);
    argv[2] = field;
    argvlen[2] = strlen(field);
    argv[3] = value;
    argvlen[3] = valuelen;
    this->reply_ = (redisReply*)redisCommandArgv(this->connect_, 4, argv, argvlen);
    if (this->reply_ == nullptr or this->reply_->type != REDIS_REPLY_INTEGER) {
        std::cerr << "Executed command [ HSet " << key << "  " << field << "  " << value << " ] failure ! " << std::endl;
        freeReplyObject(this->reply_);
        return false;
    }
    std::cerr << "Executed command [ HSet " << key << "  " << field << "  " << value << " ] success ! " << std::endl;
    freeReplyObject(this->reply_);
    return true;
}

std::string RedisManager::hget(const std::string &key, const std::string &field)
{
    const char* argv[3];
    size_t argvlen[3];
    argv[0] = "HGET";
    argvlen[0] = 4;
    argv[1] = key.c_str();
    argvlen[1] = key.length();
    argv[2] = field.c_str();
    argvlen[2] = field.length();
    this->reply_ = static_cast<redisReply*>(redisCommandArgv(this->connect_, 3, argv, argvlen));
    if (this->reply_ == nullptr || this->reply_->type == REDIS_REPLY_NIL) {
        freeReplyObject(this->reply_);
        std::cerr << "Executed command [ HGet " << key << " "<< field <<"  ] failure ! " << std::endl;
        return "";
    }
    std::string value = this->reply_->str;
    freeReplyObject(this->reply_);
    std::cerr << "Executed command [ HGet " << key << " " << field << " ] success ! " << std::endl;
    return value;
}

bool RedisManager::existskey(const std::string& key) {
    this->reply_ = static_cast<redisReply*>(redisCommand(this->connect_, "EXISTS %s", key.c_str()));
    if (this->reply_ == nullptr) {
        std::cerr << "Failed to execute EXISTS command!" << std::endl;
        return false;
    }
    bool exists = (this->reply_->type == REDIS_REPLY_INTEGER and this->reply_->integer > 0);
    freeReplyObject(this->reply_);
    std::cerr << "Executed command [ EXISTS " << key << " ] " << (exists ? "exists" : "does not exist") << " ! " << std::endl;
    return exists;
}

void RedisManager::close() {
    if (this->connect_) {
        redisFree(this->connect_);
        this->connect_ = nullptr;
        std::cerr << "Redis connection closed." << std::endl;
    }
}