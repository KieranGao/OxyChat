#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>
#include <memory>

template<class T>
class Singleton {
    // 单例基类，此处为protected作用为使派生类可以构造基类
protected:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton<T>& other) = delete;
    Singleton<T>& operator=(const Singleton<T>& other) = delete;
public:
    static std::shared_ptr<T>& getInstance() {
        static std::once_flag flag;
        static std::shared_ptr<T> instance_;// 存储唯一实例的智能指针
        // 此处不能使用make_shared(),因为此单例类的构造函数是protected的，外部函数无法访问
        std::call_once(flag, [](){
            instance_ = std::shared_ptr<T>(new T());
        });
        return instance_;
    }
};

#endif // SINGLETON_H
