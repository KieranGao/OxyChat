#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include "httpmanager.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->pwd2lineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->cancelpushButton, &QPushButton::clicked, this, &RegisterDialog::CancelToLogin);
    connect(HttpManager::getInstance().get(), &HttpManager::signal_register_finish, this, &RegisterDialog::slot_register_finish);
    // 设置errorlabel的初始状态
    ui->errorlabel->setProperty("state", "normal");
    repolish(ui->errorlabel);
    initHttpHandlers();

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
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::ErrorContent(QString &&str)
{
    ui->errorlabel->setText(str);
    ui->errorlabel->setProperty("state", "error");
    repolish(ui->errorlabel);
}

void RegisterDialog::ValidContent(QString &&str)
{
    ui->errorlabel->setText(str);
    ui->errorlabel->setProperty("state", "normal");
    repolish(ui->errorlabel);
}

void RegisterDialog::initHttpHandlers()
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

    Handlers_.insert(ReqId::ID_REGISTER, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS) {
            ErrorContent(tr("===Invalid arguments==="));
            return;
        }
        auto email = jsonObj["email"].toString();
        ValidContent(tr("===Registration finished! Page will return in 3s==="));
        qDebug() << email << " registered!";
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



void RegisterDialog::on_getveripushButton_clicked()
{
    auto email = ui->emaillineEdit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(match){
        ValidContent(tr("===No error detected==="));
        //发送http请求获取验证码
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpManager::getInstance()->PostHttpRequest(QUrl(GATESERVER_URL_PREFIX + "/get_verify_code"), json_obj, ReqId::ID_GET_VERIFY_CODE, Modules::MOD_REGISTER);

    }else{
        ErrorContent(tr("===Invalid email address==="));
    }
}

void RegisterDialog::slot_register_finish(ReqId id, const QString& res, ErrorCodes err)
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


void RegisterDialog::on_confirmpushbotton_clicked()
{

    if(ui->usernamelineEdit->text() == ""){
        ErrorContent(tr("Username cannot be empty!"));
        return;
    }
    if(ui->emaillineEdit->text() == ""){
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
    if(ui->verilineEdit->text() == ""){
        ErrorContent(tr("Verify code cannot be empty!"));
        return;
    }
    //发送http请求注册用户
    QJsonObject json_obj;
    json_obj["user"] = ui->usernamelineEdit->text();
    json_obj["email"] = ui->emaillineEdit->text();
    json_obj["password"] = xorString(ui->pwdlineEdit->text());
    json_obj["confirm"] = xorString(ui->pwd2lineEdit->text());
    json_obj["verify_code"] = ui->verilineEdit->text();
    HttpManager::getInstance()->PostHttpRequest(QUrl(GATESERVER_URL_PREFIX+"/user_register"),
                                        json_obj, ReqId::ID_REGISTER,Modules::MOD_REGISTER);
}

