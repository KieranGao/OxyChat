#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QDebug>
#include <QSettings>
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

    QString app_path = QCoreApplication::applicationDirPath();
    QString fileName = "config.ini";
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + fileName);

    // qDebug() << "Application path:" << app_path;
    // qDebug() << "Config file path:" << config_path;
    qDebug() << "Config file exists:" << QFile::exists(config_path);
    
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    GATESERVER_URL_PREFIX = "http://"+gate_host+":"+gate_port;

    // qDebug() << GATESERVER_URL_PREFIX;
    MainWindow w;
    w.show();
    return a.exec();
}
