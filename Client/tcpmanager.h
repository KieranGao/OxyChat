#ifndef TCPMANAGER_H
#define TCPMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <functional>
#include <QMap>
#include "singleton.h"
#include "global.h"

class TCPManager : public QObject, public Singleton<TCPManager>, public std::enable_shared_from_this<TCPManager>
{
    Q_OBJECT
    friend class Singleton<TCPManager>;
public:
    ~TCPManager() = default;
private:
    TCPManager();
    void initHandlers();
    void handleMessage(ReqId id, int len, QByteArray data);
    QTcpSocket socket_;
    QString host_;
    uint16_t port_;
    QByteArray buffer_;
    bool pending_; // 数据包是否完全收全
    quint16 message_id_;
    quint16 message_len_;
    QMap<ReqId, std::function<void(ReqId id, int len, QByteArray data)>> handlers_;
public slots:
    void slot_tcp_connect(ServerInfo);
    void slot_send_data(ReqId reqId, QString data);
signals:
    void signal_connect_success(bool ok);
    void signal_send_data(ReqId reqId, QString data);
    void signal_switch_chatDialog();
    void signal_login_failed(int);
};

#endif // TCPMANAGER_H
