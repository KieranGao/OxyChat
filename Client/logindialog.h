/*************************************************
    * @file: logindialog.h
    * @brief: Login Window
    *
    * @author: OxyTheCrack
    * @date: 2026/03/17
**************************************************/
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    void ErrorContent(QString&& str);
    void ValidContent(QString&& str);

private:
    Ui::LoginDialog *ui;
    void initProfile();
    void initHttpHandlers();
    bool checkEmailValid();
    bool checkPasswordValid();
    int uid_;
    QString token_;
signals:
    void ToRegister();
    void ToReset();
    void signal_connect_tcp(ServerInfo);
private slots:
    void on_LoginpushButton_clicked();
    void slot_login_finish(ReqId id, const QString& res, ErrorCodes err);
    void slot_tcp_connect_finish(bool ok);
private:
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
};

#endif // LOGINDIALOG_H
