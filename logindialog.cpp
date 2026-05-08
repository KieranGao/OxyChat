#include "logindialog.h"
#include "ui_logindialog.h"
#include "global.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->RegisterpushButton, &QPushButton::clicked, this, &LoginDialog::ToRegister);
    connect(ui->forgotbtn, &QPushButton::clicked, this, &LoginDialog::ToReset);
    ui->showpass->setProperty("showpass",false);
    connect(ui->showpass, &QPushButton::clicked, this, [=](){
        bool show = ui->showpass->property("showpass").toBool();
        show = !show;
        ui->showpass->setProperty("showpass", show);
        repolish(ui->showpass);
        if (show) {
            ui->passwordlineEdit->setEchoMode(QLineEdit::Normal);
        } else {
            ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
        }
    });
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
