/*************************************************
    * @file: registerdialog.h
    * @brief: Register Window
    *
    * @author: OxyTheCrack
    * @date: 2026/03/17
**************************************************/
#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private:
    Ui::RegisterDialog *ui;

    void ErrorContent(QString&& str);

    void ValidContent(QString&& str);

    void initHttpHandlers();
signals:
    void CancelToLogin();
private slots:
    void on_getveripushButton_clicked();
    void slot_register_finish(ReqId id, const QString& res, ErrorCodes err);
    void on_confirmpushbotton_clicked();

private:
    QMap<ReqId, std::function<void(const QJsonObject&)>> Handlers_;
};

#endif // REGISTERDIALOG_H
