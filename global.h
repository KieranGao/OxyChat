#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include <QStyle>
#include <QRegularExpression>

// 需要发送POST请求的场景
enum ReqId {
    ID_GET_VERIFY_CODE = 1, // 获取验证码
    ID_REGISTER = 2, // 注册新用户
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1, //Json解析失败
    ERR_NETWORK = 2,
};

enum Modules{
    MOD_REGISTER = 0,
};

// 用于qss的刷新
extern std::function<void(QWidget*)> repolish;
// 用于密码加密存储，使用异或加密
extern std::function<QString(QString)> xorString;

extern QString GATESERVER_URL_PREFIX;

#endif // GLOBAL_H
