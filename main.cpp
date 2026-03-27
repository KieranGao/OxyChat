#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/stylesheet.qss");
    qDebug() << "QSS path:" << qss.fileName();
    if(qss.open(QFile::ReadOnly)) {
        qDebug("Open Qss Success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    } else {
        qDebug("Open Qss Failed!");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
