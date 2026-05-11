#include "logindialog.h"
#include "ui_logindialog.h"
#include "global.h"
#include <QJsonObject>
#include "httpmanager.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->RegisterpushButton, &QPushButton::clicked, this, &LoginDialog::ToRegister);
    connect(ui->forgotbtn, &QPushButton::clicked, this, &LoginDialog::ToReset);
    ui->showpass->setProperty("showpass",false);
    initProfile();
    connect(HttpManager::getInstance().get(), &HttpManager::signal_login_finish, this, &LoginDialog::slot_login_finish);
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
    initHttpHandlers();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::initProfile()
{
    // 固定目标尺寸：300 x 300
    const int HEAD_SIZE = 300;
    // 加载原始图片
    QPixmap originalPixmap(":/avatars/profile.jpg");
    // 缩放到 300x300，保持比例 + 平滑缩放
    originalPixmap = originalPixmap.scaled(
        HEAD_SIZE, HEAD_SIZE,
        Qt::KeepAspectRatio,        // 保持宽高比，不变形
        Qt::SmoothTransformation    // 高清平滑缩放
        );
    // 创建 300x300 透明画布
    QPixmap roundedPixmap(HEAD_SIZE, HEAD_SIZE);
    roundedPixmap.fill(Qt::transparent);
    // 绘制圆角头像
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    // 圆角半径（设为 15 比较美观，可自己改）
    int radius = 15;
    QPainterPath path;
    path.addRoundedRect(0, 0, HEAD_SIZE, HEAD_SIZE, radius, radius);
    painter.setClipPath(path);
    // 居中绘制图片
    int x = (HEAD_SIZE - originalPixmap.width()) / 2;
    int y = (HEAD_SIZE - originalPixmap.height()) / 2;
    painter.drawPixmap(x, y, originalPixmap);
    // 设置到 Label
    ui->imagelabel->setPixmap(roundedPixmap);
    // 让 Label 也变成 300x300
    ui->imagelabel->setFixedSize(HEAD_SIZE, HEAD_SIZE);
}

void LoginDialog::initHttpHandlers() {
    //注册获取登录回包逻辑
    handlers_.insert(ReqId::ID_USER_LOGIN, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            ErrorContent(tr("===Invalid arguments!==="));
            return;
        }
        auto user = jsonObj["user"].toString();
        ValidContent(tr("===Successfully login to your account!==="));
        qDebug()<< "user " << user << " has login!";
    });
}

bool LoginDialog::checkEmailValid()
{
    auto user = ui->userlineEdit->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(user).hasMatch(); // 执行正则表达式匹配
    if(user.isEmpty() or !match){
        qDebug() << "Invalid email format" ;
        return false;
    }
    return true;
}

bool LoginDialog::checkPasswordValid()
{
    auto pwd = ui->passwordlineEdit->text();
    if(pwd.length() < 6){
        qDebug() << "Pass length invalid";
        return false;
    }
    return true;
}

void LoginDialog::ErrorContent(QString &&str)
{
    ui->errorlabel->setText(str);
    ui->errorlabel->setProperty("state", "error");
    repolish(ui->errorlabel);
}

void LoginDialog::ValidContent(QString &&str)
{
    ui->errorlabel->setText(str);
    ui->errorlabel->setProperty("state", "normal");
    repolish(ui->errorlabel);
}

void LoginDialog::on_LoginpushButton_clicked()
{
    qDebug()<<"login btn clicked";
    if(!checkEmailValid()){
        ErrorContent("===Invalid email address!===");
        return;
    }
    if(!checkPasswordValid()){
        ErrorContent("===Password too short!===");
        return ;
    }
    auto user = ui->userlineEdit->text();
    auto pwd = ui->passwordlineEdit->text();
    //发送http请求登录
    QJsonObject json_obj;
    json_obj["user"] = user;
    json_obj["passwd"] = xorString(pwd);
    HttpManager::getInstance()->PostHttpRequest(QUrl(GATESERVER_URL_PREFIX+"/user_login"),
                                        json_obj, ReqId::ID_USER_LOGIN,Modules::MOD_LOGIN);
}

void LoginDialog::slot_login_finish(ReqId id, const QString &res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        ErrorContent(tr("===Unknown network error!==="));
        return;
    }
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
    handlers_[id](jsonObj);
    return;
}

