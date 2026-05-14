#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class ResetDialog;
}

class ResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetDialog(QWidget *parent = nullptr);
    ~ResetDialog();
    void ErrorContent(QString&& str);
    void ValidContent(QString&& str);
    void resetText();
    void initHttpHandlers();
signals:
    void CancelToLogin();
    void ConfirmToLogin();
private slots:
    void on_getveripushButton_clicked();
    void slot_reset_finish(ReqId id, const QString& res, ErrorCodes err);
    void on_confirmbtn_clicked();

private:
    Ui::ResetDialog *ui;
private:
    QMap<ReqId, std::function<void(const QJsonObject&)>> Handlers_;
};

#endif // RESETDIALOG_H
