#ifndef TIMERBTN_H
#define TIMERBTN_H
#include <QPushButton>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

class TimerBtn : public QPushButton
{
public:
    TimerBtn(QWidget* parent = nullptr);
    ~TimerBtn();
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QTimer* timer_;
    int counter_;
};

#endif // TIMERBTN_H
