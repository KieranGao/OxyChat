#include "tcpmanager.h"
#include <QAbstractSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QDebug>

// 消息头 = 2字节ID + 2字节长度，网络字节序（大端）
TCPManager::TCPManager()
    : host_(""), port_(0), pending_(false),
    message_id_(0), message_len_(0)
{
    // 连接成功
    QObject::connect(&socket_, &QTcpSocket::connected, [&]() {
        qDebug() << "Connected to server!";
        emit signal_connect_success(true);
    });

    // 接收数据
    QObject::connect(&socket_, &QTcpSocket::readyRead, [&]() {
        buffer_.append(socket_.readAll());
        while (true) {
            // 还没读取消息头
            if (!pending_) {
                // 头长度不足：2+2=4字节
                if (buffer_.size() < 4) {
                    break;
                }
                // 从缓冲区前4字节解析头（强制网络字节序）
                QDataStream stream(buffer_.left(4));
                stream.setByteOrder(QDataStream::BigEndian);
                stream >> message_id_ >> message_len_;
                // 移除头部
                buffer_ = buffer_.mid(4);
                pending_ = true;
                qDebug() << "Recv Header: ID=" << message_id_ << " Len=" << message_len_;
            }
            // 待消息体足够
            if (buffer_.size() < message_len_) {
                break;
            }
            // 读取消息体
            QByteArray body = buffer_.left(message_len_);
            buffer_ = buffer_.mid(message_len_);
            pending_ = false;
            qDebug() << "Recv Body:" << body;
            handleMessage(ReqId(message_id_), message_len_, body);
        }
    });

    // 错误处理
    QObject::connect(&socket_, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
                     [&](QAbstractSocket::SocketError socketError) {
                         Q_UNUSED(socketError)
                         qDebug() << "TCP Error:" << socket_.errorString();
                     });

    // 断开连接
    QObject::connect(&socket_, &QTcpSocket::disconnected, [&]() {
        qDebug() << "Disconnected from server.";
    });

    // 发送信号绑定
    QObject::connect(this, &TCPManager::signal_send_data, this, &TCPManager::slot_send_data);

    initHandlers();
}

// 登录消息处理
void TCPManager::initHandlers()
{
    handlers_.insert(ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "Handle ID:" << id << "Data:" << data;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (jsonDoc.isNull()) {
            qDebug() << "Json parse failed";
            emit signal_login_failed(ErrorCodes::ERR_JSON);
            return;
        }
        QJsonObject obj = jsonDoc.object();
        if (!obj.contains("error")) {
            emit signal_login_failed(ErrorCodes::ERR_JSON);
            return;
        }
        int err = obj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            emit signal_login_failed(err);
            return;
        }
        // UserMgr::GetInstance()->SetUid(jsonObj["uid"].toInt());
        // UserMgr::GetInstance()->SetName(jsonObj["name"].toString());
        // UserMgr::GetInstance()->SetToken(jsonObj["token"].toString());
        emit signal_switch_chatDialog();
    });
}

void TCPManager::handleMessage(ReqId id, int len, QByteArray data)
{
    auto it = handlers_.find(id);
    if (it == handlers_.end()) {
        qDebug() << "No handler for ID:" << id;
        return;
    }
    it.value()(id, len, data);
}

void TCPManager::slot_tcp_connect(ServerInfo si)
{
    qDebug() << "Connecting to:" << si.host << si.port;
    host_ = si.host;
    port_ = si.port.toUInt();
    socket_.connectToHost(si.host, port_);
}

void TCPManager::slot_send_data(ReqId reqId, QString data)
{
    if (socket_.state() != QTcpSocket::ConnectedState) {
        qDebug() << "Send failed: not connected!";
        return;
    }

    QByteArray body = data.toUtf8();
    quint16 id = static_cast<quint16>(reqId);
    quint16 len = static_cast<quint16>(body.size());

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 统一使用大端网络字节序
    out.setByteOrder(QDataStream::BigEndian);
    out << id << len;
    block.append(body);
    socket_.write(block);
    socket_.flush(); // 强制发送
    qDebug() << "Send: ID=" << id << " Len=" << len << " Body=" << body;
}