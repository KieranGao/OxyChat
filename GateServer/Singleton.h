#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <mutex>
#include <iostream>

// 单例基类，使用CRTP（Curiously Recurring Template Pattern）实现单例模式
template<class T>
class Singleton {

protected:
    Singleton() = default;
    ~Singleton() = default;
    Singleton<T>& operator=(const Singleton<T>&) = delete;
    Singleton(const Singleton<T>&) = delete;

public:
    static std::shared_ptr<T> getInstance() {
        static std::shared_ptr<T> instance;
        static std::once_flag flag;
        std::call_once(flag, [](){
            // 注意不能使用make_shared，因为构造函数是私有的，make_shared无法访问
            instance = std::shared_ptr<T>(new T());
        });
        return instance;
    }
};



#endif /* SINGLETON_H */



