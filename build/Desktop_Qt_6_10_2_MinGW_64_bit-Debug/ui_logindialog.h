/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
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

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *imagelabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *userlabel;
    QLineEdit *userlineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *passwordlabel;
    QLineEdit *passwordlineEdit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *forgetlabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *LoginpushButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *RegisterpushButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginDialog->sizePolicy().hasHeightForWidth());
        LoginDialog->setSizePolicy(sizePolicy);
        LoginDialog->setMinimumSize(QSize(400, 600));
        LoginDialog->setMaximumSize(QSize(400, 600));
        verticalLayout_2 = new QVBoxLayout(LoginDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(LoginDialog);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(800, 400));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        imagelabel = new QLabel(widget);
        imagelabel->setObjectName("imagelabel");
        imagelabel->setEnabled(true);
        imagelabel->setMinimumSize(QSize(100, 100));
        imagelabel->setMaximumSize(QSize(300, 300));
        imagelabel->setPixmap(QPixmap(QString::fromUtf8(":/icons/oxy.jpg")));
        imagelabel->setScaledContents(true);
        imagelabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        imagelabel->setWordWrap(false);
        imagelabel->setOpenExternalLinks(false);

        horizontalLayout_3->addWidget(imagelabel);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, -1, 10, -1);
        userlabel = new QLabel(LoginDialog);
        userlabel->setObjectName("userlabel");
        userlabel->setMinimumSize(QSize(0, 25));
        userlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(userlabel);

        userlineEdit = new QLineEdit(LoginDialog);
        userlineEdit->setObjectName("userlineEdit");
        userlineEdit->setMinimumSize(QSize(0, 25));
        userlineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(userlineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, -1, 10, -1);
        passwordlabel = new QLabel(LoginDialog);
        passwordlabel->setObjectName("passwordlabel");
        passwordlabel->setMinimumSize(QSize(0, 25));
        passwordlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(passwordlabel);

        passwordlineEdit = new QLineEdit(LoginDialog);
        passwordlineEdit->setObjectName("passwordlineEdit");
        passwordlineEdit->setMinimumSize(QSize(0, 25));
        passwordlineEdit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(passwordlineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, -1, 10, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        forgetlabel = new QLabel(LoginDialog);
        forgetlabel->setObjectName("forgetlabel");
        forgetlabel->setMinimumSize(QSize(0, 25));
        forgetlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(forgetlabel);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        LoginpushButton = new QPushButton(LoginDialog);
        LoginpushButton->setObjectName("LoginpushButton");
        LoginpushButton->setMinimumSize(QSize(100, 30));
        LoginpushButton->setMaximumSize(QSize(100, 30));

        horizontalLayout_6->addWidget(LoginpushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        RegisterpushButton = new QPushButton(LoginDialog);
        RegisterpushButton->setObjectName("RegisterpushButton");
        RegisterpushButton->setMinimumSize(QSize(100, 30));
        RegisterpushButton->setMaximumSize(QSize(100, 30));

        horizontalLayout_7->addWidget(RegisterpushButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        imagelabel->setText(QString());
        userlabel->setText(QCoreApplication::translate("LoginDialog", "Username:", nullptr));
        passwordlabel->setText(QCoreApplication::translate("LoginDialog", "Password:", nullptr));
        forgetlabel->setText(QCoreApplication::translate("LoginDialog", "Forget password? ", nullptr));
        LoginpushButton->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        RegisterpushButton->setText(QCoreApplication::translate("LoginDialog", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
