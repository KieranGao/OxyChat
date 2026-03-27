#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , login_dlg_(nullptr)
    , register_dlg_(nullptr)
{
    ui->setupUi(this);

    login_dlg_ = new LoginDialog(this);
    register_dlg_ = new RegisterDialog(this);
    login_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    register_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    QVBoxLayout *centralLayout = new QVBoxLayout(ui->centralwidget);
    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(login_dlg_);
    centralLayout->addWidget(register_dlg_);

    login_dlg_->show();
    register_dlg_->hide();

    connect(login_dlg_, &LoginDialog::ToRegister, this, &MainWindow::SlotToRegister);
    connect(register_dlg_, &RegisterDialog::CancelToLogin, this, &MainWindow::SlotToLogin);
}

MainWindow::~MainWindow()
{
    delete ui;
    // 无需手动删除对话框：父对象自动释放
}

void MainWindow::SlotToRegister()
{
    login_dlg_->hide();
    register_dlg_->show();
}

void MainWindow::SlotToLogin()
{
    register_dlg_->hide();
    login_dlg_->show();
}
