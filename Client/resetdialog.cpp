#include "resetdialog.h"
#include "ui_resetdialog.h"
#include "global.h"
#include "httpmanager.h"
#include <QTimer>
ResetDialog::ResetDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ResetDialog)
{
    ui->setupUi(this);
    ui->errorlabel->setProperty("state", "normal");
    repolish(ui->errorlabel);
    connect(ui->cancelbtn, &QPushButton::clicked, this, &ResetDialog::CancelToLogin);
    connect(HttpManager::getInstance().get(), &HttpManager::signal_reset_finish, this, &ResetDialog::slot_reset_finish);

    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->showpass->setProperty("showpass",false);
    ui->pwd2lineEdit->setEchoMode(QLineEdit::Password);
    ui->showconfirm->setProperty("showpass",false);
    repolish(ui->showpass);
    repolish(ui->showconfirm);

    connect(ui->showpass, &QPushButton::clicked, this, [=](){
        bool show = ui->showpass->property("showpass").toBool();
        show = !show;
        ui->showpass->setProperty("showpass", show);
        repolish(ui->showpass);
        if (show) {
            ui->pwdlineEdit->setEchoMode(QLineEdit::Normal);
        } else {
            ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
        }
    });

    connect(ui->showconfirm, &QPushButton::clicked, this, [=](){
        bool show = ui->showconfirm->property("showpass").toBool();
        show = !show;
        ui->showconfirm->setProperty("showpass", show);
        repolish(ui->showconfirm);
        if (show) {
            ui->pwd2lineEdit->setEchoMode(QLineEdit::Normal);
        } else {
            ui->pwd2lineEdit->setEchoMode(QLineEdit::Password);
        }
    });
    initHttpHandlers();
}

ResetDialog::~ResetDialog()
{
    delete ui;
}

void ResetDialog::resetText() {
    ui->namelineEdit->clear();
    ui->pwd2lineEdit->clear();
    ui->pwdlineEdit->clear();
    ui->emaillineedit->clear();
    ui->codelineedit->clear();
}


void ResetDialog::ErrorContent(QString &&str)
{
    ui->errorlabel->setText(str);
    ui->errorlabel->setProperty("state", "error");
    repolish(ui->errorlabel);
}

void ResetDialog::ValidContent(QString &&str)
{
    ui->errorlabel->setText(str);
    ui->errorlabel->setProperty("state", "normal");
    repolish(ui->errorlabel);
}

void ResetDialog::initHttpHandlers()
{
    // 注册Handlers_中的注册以及验证码回包的逻辑
    Handlers_.insert(ReqId::ID_GET_VERIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS) {
            ErrorContent(tr("===Unknown errors==="));
            return;
        }
        auto email = jsonObj["email"].toString();
        ValidContent(tr("===The verification code has been sent==="));
        qDebug() << "email is " << email;
    });

    Handlers_.insert(ReqId::ID_RESET, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        qDebug() << "ID_RESET";
        if(error != ErrorCodes::SUCCESS) {
            ErrorContent(tr("===Error! Verify code may not match or username or email maybe not exist!==="));
            return;
        }
        auto username = jsonObj["user"].toString();
        ValidContent(tr("===Password reset process finished! Page will return in 3s==="));
        qDebug() << username << " password reseted!";
        QTimer *timer_ = new QTimer(this);
        // 定时器单次触发
        timer_->setSingleShot(true);
        connect(timer_, &QTimer::timeout, this, [this, timer_](){
            timer_->stop();
            timer_->deleteLater();
            emit ConfirmToLogin();
        });
        // 3000毫秒
        timer_->start(3000);
        return;
    });
}



void ResetDialog::on_getveripushButton_clicked()
{
    auto email = ui->emaillineedit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        ValidContent(tr("===No error detected==="));
        //发送http请求获取验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        qDebug() << email;
        HttpManager::getInstance()->PostHttpRequest(QUrl(GATESERVER_URL_PREFIX + "/get_verify_code"), json_obj, ReqId::ID_GET_VERIFY_CODE, Modules::MOD_RESETPASS);
    }else{
        ErrorContent(tr("===Invalid email address==="));
    }
}

void ResetDialog::slot_reset_finish(ReqId id, const QString& res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS) {
        ErrorContent(tr("===Unknown network error==="));
        return;
    }
    // 此时解析 JSON 字符串, res 需转化为 QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()) {
        ErrorContent(tr("===Parse JSON error==="));
        return;
    }
    if(!jsonDoc.isObject()){
        ErrorContent(tr("===Parse JSON error==="));
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    Handlers_[id](jsonObj);
    return;
}


void ResetDialog::on_confirmbtn_clicked()
{
    if(ui->namelineEdit->text() == ""){
        ErrorContent(tr("Username cannot be empty!"));
        return;
    }
    if(ui->emaillineedit->text() == ""){
        ErrorContent(tr("Email address cannot be empty!"));
        return;
    }
    if(ui->pwdlineEdit->text() == ""){
        ErrorContent(tr("Password cannot be empty!"));
        return;
    }
    if(ui->pwd2lineEdit->text() == ""){
        ErrorContent(tr("Plase confirm the password!"));
        return;
    }
    if(ui->pwdlineEdit->text() != ui->pwd2lineEdit->text()){
        ErrorContent(tr("Password doesn't match the same!"));
        return;
    }
    if(ui->codelineedit->text() == ""){
        ErrorContent(tr("Verify code cannot be empty!"));
        return;
    }
    //发送http请求修改密码
    qDebug() << "RESET START POST HTTP REQUEST!";
    QJsonObject json_obj;
    json_obj["user"] = ui->namelineEdit->text();
    json_obj["email"] = ui->emaillineedit->text();
    json_obj["password"] = xorString(ui->pwdlineEdit->text());
    json_obj["confirm"] = xorString(ui->pwd2lineEdit->text());
    json_obj["verify_code"] = ui->codelineedit->text();
    HttpManager::getInstance()->PostHttpRequest(QUrl(GATESERVER_URL_PREFIX+"/user_resetpass"),
                                                json_obj, ReqId::ID_RESET,Modules::MOD_RESETPASS);
}
