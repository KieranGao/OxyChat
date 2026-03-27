/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QSpacerItem *verticalSpacer;
    QLabel *errorlabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *usernamelabel;
    QLineEdit *usernamelineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *emaillabel;
    QLineEdit *emaillineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *pwdlabel;
    QLineEdit *pwdlineEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *pwd2label2;
    QLineEdit *pwd2lineEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *verlabel;
    QLineEdit *verilineEdit;
    QPushButton *getveripushButton;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *confirmpushbotton;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelpushButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(400, 600);
        RegisterDialog->setMinimumSize(QSize(400, 600));
        RegisterDialog->setMaximumSize(QSize(400, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/OxyChatIcon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        RegisterDialog->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(RegisterDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(RegisterDialog);
        widget->setObjectName("widget");

        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        errorlabel = new QLabel(RegisterDialog);
        errorlabel->setObjectName("errorlabel");
        errorlabel->setMinimumSize(QSize(0, 25));
        errorlabel->setMaximumSize(QSize(16777215, 25));
        errorlabel->setStyleSheet(QString::fromUtf8(""));
        errorlabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(errorlabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, -1, 10, -1);
        usernamelabel = new QLabel(RegisterDialog);
        usernamelabel->setObjectName("usernamelabel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(usernamelabel->sizePolicy().hasHeightForWidth());
        usernamelabel->setSizePolicy(sizePolicy);
        usernamelabel->setMinimumSize(QSize(0, 25));
        usernamelabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(usernamelabel);

        usernamelineEdit = new QLineEdit(RegisterDialog);
        usernamelineEdit->setObjectName("usernamelineEdit");
        usernamelineEdit->setMinimumSize(QSize(0, 25));
        usernamelineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(usernamelineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 10, 0);
        emaillabel = new QLabel(RegisterDialog);
        emaillabel->setObjectName("emaillabel");
        emaillabel->setMinimumSize(QSize(0, 25));
        emaillabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(emaillabel);

        emaillineEdit = new QLineEdit(RegisterDialog);
        emaillineEdit->setObjectName("emaillineEdit");
        emaillineEdit->setMinimumSize(QSize(0, 25));
        emaillineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(emaillineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, -1, 10, -1);
        pwdlabel = new QLabel(RegisterDialog);
        pwdlabel->setObjectName("pwdlabel");
        pwdlabel->setMinimumSize(QSize(0, 25));
        pwdlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(pwdlabel);

        pwdlineEdit = new QLineEdit(RegisterDialog);
        pwdlineEdit->setObjectName("pwdlineEdit");
        pwdlineEdit->setMinimumSize(QSize(0, 25));
        pwdlineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(pwdlineEdit);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, -1, 10, -1);
        pwd2label2 = new QLabel(RegisterDialog);
        pwd2label2->setObjectName("pwd2label2");
        pwd2label2->setMinimumSize(QSize(0, 25));
        pwd2label2->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(pwd2label2);

        pwd2lineEdit = new QLineEdit(RegisterDialog);
        pwd2lineEdit->setObjectName("pwd2lineEdit");
        pwd2lineEdit->setMinimumSize(QSize(0, 25));
        pwd2lineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(pwd2lineEdit);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, -1, 10, -1);
        verlabel = new QLabel(RegisterDialog);
        verlabel->setObjectName("verlabel");
        verlabel->setMinimumSize(QSize(0, 25));
        verlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_8->addWidget(verlabel);

        verilineEdit = new QLineEdit(RegisterDialog);
        verilineEdit->setObjectName("verilineEdit");
        verilineEdit->setMinimumSize(QSize(0, 25));
        verilineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_8->addWidget(verilineEdit);

        getveripushButton = new QPushButton(RegisterDialog);
        getveripushButton->setObjectName("getveripushButton");

        horizontalLayout_8->addWidget(getveripushButton);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(10);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(50, -1, 50, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        confirmpushbotton = new QPushButton(RegisterDialog);
        confirmpushbotton->setObjectName("confirmpushbotton");
        confirmpushbotton->setMinimumSize(QSize(100, 30));
        confirmpushbotton->setMaximumSize(QSize(100, 30));

        horizontalLayout_9->addWidget(confirmpushbotton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        cancelpushButton = new QPushButton(RegisterDialog);
        cancelpushButton->setObjectName("cancelpushButton");
        cancelpushButton->setMinimumSize(QSize(100, 30));
        cancelpushButton->setMaximumSize(QSize(100, 30));

        horizontalLayout_9->addWidget(cancelpushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Register", nullptr));
        errorlabel->setText(QCoreApplication::translate("RegisterDialog", "===No error detected===", nullptr));
        usernamelabel->setText(QCoreApplication::translate("RegisterDialog", "Username:", nullptr));
        emaillabel->setText(QCoreApplication::translate("RegisterDialog", "Email:", nullptr));
        pwdlabel->setText(QCoreApplication::translate("RegisterDialog", "Password:", nullptr));
        pwd2label2->setText(QCoreApplication::translate("RegisterDialog", "Confirm password:", nullptr));
        verlabel->setText(QCoreApplication::translate("RegisterDialog", "Verification code:", nullptr));
        getveripushButton->setText(QCoreApplication::translate("RegisterDialog", "Get code", nullptr));
        confirmpushbotton->setText(QCoreApplication::translate("RegisterDialog", "Confirm", nullptr));
        cancelpushButton->setText(QCoreApplication::translate("RegisterDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
