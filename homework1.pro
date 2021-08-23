QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chessboard.cpp \
    chessgrid.cpp \
    chesspiece.cpp \
    client.cpp \
    enddialog.cpp \
    global.cpp \
    grid.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    server.cpp \
    validator.cpp

HEADERS += \
    chessboard.h \
    chessgrid.h \
    chesspiece.h \
    chessrules.h \
    client.h \
    enddialog.h \
    global.h \
    grid.h \
    mainwindow.h \
    player.h \
    server.h \
    validator.h

FORMS += \
    chessboard.ui \
    chessgrid.ui \
    client.ui \
    enddialog.ui \
    mainwindow.ui \
    server.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
