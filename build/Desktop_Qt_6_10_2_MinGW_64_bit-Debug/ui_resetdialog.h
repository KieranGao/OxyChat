/********************************************************************************
** Form generated from reading UI file 'resetdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETDIALOG_H
#define UI_RESETDIALOG_H

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
#include "timerbtn.h"

QT_BEGIN_NAMESPACE

class Ui_ResetDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *errorlabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *namelabel;
    QLineEdit *namelineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pwdlabel;
    QLineEdit *pwdlineEdit;
    QPushButton *showpass;
    QHBoxLayout *horizontalLayout_2;
    QLabel *confirmpwdlabel;
    QLineEdit *pwd2lineEdit;
    QPushButton *showconfirm;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *emaillabel;
    QLineEdit *emaillineedit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *codelabel;
    QLineEdit *codelineedit;
    TimerBtn *getveripushButton;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *confirmbtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelbtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ResetDialog)
    {
        if (ResetDialog->objectName().isEmpty())
            ResetDialog->setObjectName("ResetDialog");
        ResetDialog->resize(400, 600);
        ResetDialog->setMinimumSize(QSize(400, 600));
        ResetDialog->setMaximumSize(QSize(1000, 600));
        verticalLayoutWidget = new QWidget(ResetDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 581));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        errorlabel = new QLabel(verticalLayoutWidget);
        errorlabel->setObjectName("errorlabel");
        errorlabel->setMinimumSize(QSize(0, 25));
        errorlabel->setMaximumSize(QSize(16777215, 25));

        verticalLayout_2->addWidget(errorlabel, 0, Qt::AlignmentFlag::AlignHCenter);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        namelabel = new QLabel(verticalLayoutWidget);
        namelabel->setObjectName("namelabel");
        namelabel->setMinimumSize(QSize(0, 25));
        namelabel->setMaximumSize(QSize(100, 25));

        horizontalLayout_4->addWidget(namelabel);

        namelineEdit = new QLineEdit(verticalLayoutWidget);
        namelineEdit->setObjectName("namelineEdit");

        horizontalLayout_4->addWidget(namelineEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pwdlabel = new QLabel(verticalLayoutWidget);
        pwdlabel->setObjectName("pwdlabel");
        pwdlabel->setMinimumSize(QSize(0, 25));
        pwdlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(pwdlabel);

        pwdlineEdit = new QLineEdit(verticalLayoutWidget);
        pwdlineEdit->setObjectName("pwdlineEdit");

        horizontalLayout_3->addWidget(pwdlineEdit);

        showpass = new QPushButton(verticalLayoutWidget);
        showpass->setObjectName("showpass");
        showpass->setMinimumSize(QSize(20, 20));
        showpass->setMaximumSize(QSize(20, 20));
        showpass->setStyleSheet(QString::fromUtf8("QPushButton[showpass = \"false\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/invisible.png);\n"
"}\n"
"\n"
"QPushButton[showpass = \"true\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/visible.png);\n"
"}\n"
"\n"
"QPushButton:hover[showpass = \"true\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/visiblehover.png);\n"
"}\n"
"\n"
"QPushButton:hover[showpass = \"false\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/invisiblehover.png);\n"
"}"));

        horizontalLayout_3->addWidget(showpass);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        confirmpwdlabel = new QLabel(verticalLayoutWidget);
        confirmpwdlabel->setObjectName("confirmpwdlabel");
        confirmpwdlabel->setMinimumSize(QSize(0, 25));
        confirmpwdlabel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(confirmpwdlabel);

        pwd2lineEdit = new QLineEdit(verticalLayoutWidget);
        pwd2lineEdit->setObjectName("pwd2lineEdit");

        horizontalLayout_2->addWidget(pwd2lineEdit);

        showconfirm = new QPushButton(verticalLayoutWidget);
        showconfirm->setObjectName("showconfirm");
        showconfirm->setMinimumSize(QSize(20, 20));
        showconfirm->setMaximumSize(QSize(20, 20));
        showconfirm->setStyleSheet(QString::fromUtf8("QPushButton[showpass = \"false\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/invisible.png);\n"
"}\n"
"\n"
"QPushButton[showpass = \"true\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/visible.png);\n"
"}\n"
"\n"
"QPushButton:hover[showpass = \"true\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/visiblehover.png);\n"
"}\n"
"\n"
"QPushButton:hover[showpass = \"false\"] {\n"
"    border: none;           \n"
"    background-color: transparent;\n"
"    border-image: url(:/icons/invisiblehover.png);\n"
"}"));

        horizontalLayout_2->addWidget(showconfirm);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        emaillabel = new QLabel(verticalLayoutWidget);
        emaillabel->setObjectName("emaillabel");

        horizontalLayout_5->addWidget(emaillabel);

        emaillineedit = new QLineEdit(verticalLayoutWidget);
        emaillineedit->setObjectName("emaillineedit");

        horizontalLayout_5->addWidget(emaillineedit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        codelabel = new QLabel(verticalLayoutWidget);
        codelabel->setObjectName("codelabel");

        horizontalLayout_7->addWidget(codelabel);

        codelineedit = new QLineEdit(verticalLayoutWidget);
        codelineedit->setObjectName("codelineedit");

        horizontalLayout_7->addWidget(codelineedit);

        getveripushButton = new TimerBtn(verticalLayoutWidget);
        getveripushButton->setObjectName("getveripushButton");

        horizontalLayout_7->addWidget(getveripushButton);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        confirmbtn = new QPushButton(verticalLayoutWidget);
        confirmbtn->setObjectName("confirmbtn");
        confirmbtn->setMinimumSize(QSize(100, 30));
        confirmbtn->setMaximumSize(QSize(100, 30));

        horizontalLayout_6->addWidget(confirmbtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        cancelbtn = new QPushButton(verticalLayoutWidget);
        cancelbtn->setObjectName("cancelbtn");
        cancelbtn->setMinimumSize(QSize(100, 30));
        cancelbtn->setMaximumSize(QSize(100, 30));

        horizontalLayout_6->addWidget(cancelbtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(ResetDialog);

        QMetaObject::connectSlotsByName(ResetDialog);
    } // setupUi

    void retranslateUi(QDialog *ResetDialog)
    {
        ResetDialog->setWindowTitle(QCoreApplication::translate("ResetDialog", "Dialog", nullptr));
        errorlabel->setText(QCoreApplication::translate("ResetDialog", "===No error detected===", nullptr));
        namelabel->setText(QCoreApplication::translate("ResetDialog", "Username:", nullptr));
        pwdlabel->setText(QCoreApplication::translate("ResetDialog", "New password:", nullptr));
        showpass->setText(QString());
        confirmpwdlabel->setText(QCoreApplication::translate("ResetDialog", "Confirm password:", nullptr));
        showconfirm->setText(QString());
        emaillabel->setText(QCoreApplication::translate("ResetDialog", "Email:", nullptr));
        codelabel->setText(QCoreApplication::translate("ResetDialog", "Verifycation code:", nullptr));
        getveripushButton->setText(QCoreApplication::translate("ResetDialog", "Get code", nullptr));
        confirmbtn->setText(QCoreApplication::translate("ResetDialog", "Confirm", nullptr));
        cancelbtn->setText(QCoreApplication::translate("ResetDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResetDialog: public Ui_ResetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETDIALOG_H
