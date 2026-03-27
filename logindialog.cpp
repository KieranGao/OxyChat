#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->RegisterpushButton, &QPushButton::clicked, this, &LoginDialog::ToRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
