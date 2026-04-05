#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H
#include "singleton.h"
#include "global.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QJsonObject> // 转为JSON
#include <QJsonDocument> // 解析JSON

// CRTP
class HttpManager :public QObject, public Singleton<HttpManager>,
                    public std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT

public: // 析构置为共有，是需要保证单例类shared_ptr析构对象时能访问HttpManager类的析构函数
    ~HttpManager();
    // 发送请求要用到请求的url，请求的数据(json或者protobuf序列化)，以及请求的id，以及哪个模块发出的请求mod
    void PostHttpRequest(const QUrl& url, QJsonObject json, ReqId req_id, Modules mod);

private:
    friend class Singleton<HttpManager>; // 需要置为友元类，因为单例类实例化HttpManager时需要调用其构造函数
    HttpManager();

    QNetworkAccessManager manager_;
private slots:
    void slot_http_finish(ReqId id, const QString& res, ErrorCodes err, Modules mod);
signals:
    void signal_http_finish(ReqId id,const QString& res, ErrorCodes err, Modules mod);
    void signal_register_finish(ReqId id, const QString& res, ErrorCodes err);
};

#endif // HTTPMANAGER_H
