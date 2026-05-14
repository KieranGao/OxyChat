#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "resetdialog.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , login_dlg_(nullptr)
    , register_dlg_(nullptr)
    , reset_dlg_(nullptr)
{
    ui->setupUi(this);

    login_dlg_ = new LoginDialog(this);
    register_dlg_ = new RegisterDialog(this);
    reset_dlg_ = new ResetDialog(this);
    login_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    register_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    reset_dlg_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    QVBoxLayout *centralLayout = new QVBoxLayout(ui->centralwidget);
    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(login_dlg_);
    centralLayout->addWidget(register_dlg_);
    centralLayout->addWidget(reset_dlg_);
    login_dlg_->show();
    register_dlg_->hide();
    reset_dlg_->hide();
    connect(login_dlg_, &LoginDialog::ToRegister, this, &MainWindow::SlotToRegister);
    connect(login_dlg_, &LoginDialog::ToReset, this, &MainWindow::SlotToReset);
    connect(register_dlg_, &RegisterDialog::CancelToLogin, this, &MainWindow::SlotToLogin);
    connect(register_dlg_, &RegisterDialog::ConfirmToLogin, this, &MainWindow::SlotToLogin);
    connect(reset_dlg_, &ResetDialog::CancelToLogin, this, &MainWindow::SlotToLogin);
    connect(reset_dlg_, &ResetDialog::ConfirmToLogin, this, &MainWindow::SlotToLogin);
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
    if(!register_dlg_->isHidden())
    {
        register_dlg_->resetText();
        register_dlg_->hide();
    }
    if(!reset_dlg_->isHidden())
    {
        reset_dlg_->resetText();
        reset_dlg_->hide();
    }
    login_dlg_->show();
}

void MainWindow::SlotToReset() {
    login_dlg_->hide();
    reset_dlg_->show();
}
