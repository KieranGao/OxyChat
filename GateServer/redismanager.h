#ifndef REDISMANAGER_H
#define REDISMANAGER_H

#include <hiredis/hiredis.h>
#include "singleton.h"
#include "global.h"
class RedisManager : public Singleton<RedisManager> {

    friend class Singleton<RedisManager>;
public:
    ~RedisManager();
    bool connect(const std::string& host, int port);
    bool set(const std::string& key, const std::string& value);
    bool get(const std::string& key, std::string& value);
    bool del(const std::string& key);
    bool auth(const std::string& password);
    bool lpush(const std::string& key, const std::string& value);
    bool rpush(const std::string& key, const std::string& value);
    bool lpop(const std::string& key, std::string& value);
    bool rpop(const std::string& key, std::string& value);
    bool existskey(const std::string& key);
    bool hset(const std::string& key, const std::string& field, const std::string& value);
    bool hset(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
    std::string hget(const std::string &key, const std::string &hkey);
    void close();
private:
    RedisManager();
    redisContext* connect_;
    redisReply* reply_;
};


#endif /* REDISMANAGER_H */


/*

void TestRedisManager() {

    assert(RedisManager::getInstance()->connect("127.0.0.1", 6379));
    assert(RedisManager::getInstance()->auth("123456"));
    assert(RedisManager::getInstance()->set("blogwebsite","KieranGao.github.io"));
    std::string value="";
    assert(RedisManager::getInstance()->get("blogwebsite", value) );
    assert(RedisManager::getInstance()->get("nonekey", value) == false);
    assert(RedisManager::getInstance()->hset("bloginfo","blogwebsite", "KieranGao.github.io"));
    assert(RedisManager::getInstance()->hget("bloginfo","blogwebsite") != "");
    assert(RedisManager::getInstance()->existskey("bloginfo"));
    assert(RedisManager::getInstance()->del("bloginfo"));
    assert(RedisManager::getInstance()->del("bloginfo") == false);
    assert(RedisManager::getInstance()->existskey("bloginfo") == false);
    assert(RedisManager::getInstance()->lpush("lpushkey1", "lpushvalue1"));
    assert(RedisManager::getInstance()->lpush("lpushkey1", "lpushvalue2"));
    assert(RedisManager::getInstance()->lpush("lpushkey1", "lpushvalue3"));
    assert(RedisManager::getInstance()->rpop("lpushkey1", value));
    assert(RedisManager::getInstance()->rpop("lpushkey1", value));
    assert(RedisManager::getInstance()->lpop("lpushkey1", value));
    assert(RedisManager::getInstance()->lpop("lpushkey2", value)==false);
    RedisManager::getInstance()->close();
}

*/