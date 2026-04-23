QT       += core gui
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    global.cpp \
    httpmanager.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    registerdialog.cpp \
    timerbtn.cpp

HEADERS += \
    global.h \
    httpmanager.h \
    logindialog.h \
    mainwindow.h \
    registerdialog.h \
    singleton.h \
    timerbtn.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    registerdialog.ui

RC_ICONS = icons/OxyChatIcon.ico

DESTDIR = ./bin

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

# 自动复制 config.ini 到输出目录（Debug/Release 都复制，跨平台）
CONFIG(release, debug|release): CONFIG(Release, Release|Debug) {
    win32 {
        QMAKE_POST_LINK += copy /Y \"$$PWD/config.ini\" \"$$OUT_PWD/$$DESTDIR/\"
    } else {
        QMAKE_POST_LINK += cp -f \"$$PWD/config.ini\" \"$$OUT_PWD/$$DESTDIR/\"
    }
}

# Debug 也复制
CONFIG(debug, debug|release) {
    win32 {
        QMAKE_POST_LINK += copy /Y \"$$PWD/config.ini\" \"$$OUT_PWD/$$DESTDIR/\"
    } else {
        QMAKE_POST_LINK += cp -f \"$$PWD/config.ini\" \"$$OUT_PWD/$$DESTDIR/\"
    }
}

DISTFILES += \
    config.ini
