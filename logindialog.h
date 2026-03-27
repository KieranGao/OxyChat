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

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();


private:
    Ui::LoginDialog *ui;
signals:
    void ToRegister();
};

#endif // LOGINDIALOG_H
