#include "httpmanager.h"


HttpManager::HttpManager() {
    QObject::connect(this, &HttpManager::signal_http_finish, this, &HttpManager::slot_http_finish);
}

HttpManager::~HttpManager() {
}

void HttpManager::PostHttpRequest(const QUrl& url, QJsonObject json, ReqId req_id, Modules mod)
{
    //创建一个HTTP POST请求，并设置请求头和请求体
    QByteArray data = QJsonDocument(json).toJson(); // 此处为JSON格式的请求体
    //通过url构造请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    //发送请求，处理响应, 获取自己的智能指针，构造伪闭包并增加智能指针引用计数
    auto self = shared_from_this();
    QNetworkReply *reply = manager_.post(request, data);
    // 关联信号，异步处理相应
    QObject::connect(reply, &QNetworkReply::finished, [reply, self, req_id, mod](){ // 捕获闭包的self，若使用this可能会访问已经析构的数据（因为是异步处理）
        //处理错误的情况
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->errorString();
            //发送信号通知完成
            emit self->signal_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater(); // 调用deleteLater()后，当reply不再使用时Qt会自动回收
            return;
        }
        //无错误则读回请求
        QString res = reply->readAll();
        //发送信号通知完成
        emit self->signal_http_finish(req_id, res, ErrorCodes::SUCCESS,mod);
        reply->deleteLater();
        return;
    });
}

void HttpManager::slot_http_finish(ReqId id, const QString &res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::MOD_REGISTER) {
        emit signal_register_finish(id, res, err);
    }
}
