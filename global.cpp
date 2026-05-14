#include "global.h"

std::function<void(QWidget*)> repolish =[](QWidget *w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};

std::function<QString(QString)> xorString  = [](QString input) {
    QString res = input;
    int len = input.length();
    len %= 255;
    for(int i=0;i<len;i++) {
        res[i] = QChar(static_cast<ushort>(input[i].unicode() ^ static_cast<ushort>(len)));
    }
    return res;
};


QString GATESERVER_URL_PREFIX = "";