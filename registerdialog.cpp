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
            ErrorContent(tr("===Invalid JSON arguments==="));
            return;
        }
        auto email = jsonObj["email"].toString();
        ValidContent(tr("===The verification code has been sent==="));
        qDebug() << "email is " << email;
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

