#-------------------------------------------------
#
# Project created by QtCreator 2019-09-03T21:23:29
#
#-------------------------------------------------

QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FM20
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Club.cpp \
        ClubDatabase.cpp \
        CreateGame.cpp \
        Fixture.cpp \
        GameMenu.cpp \
        League.cpp \
        Main.cpp \
        MainWindow.cpp \
        Manager.cpp \
        Match.cpp \
        MatchEngine.cpp \
        Player.cpp \
        PlayerDatabase.cpp \
        Tactic.cpp

HEADERS += \
        Club.h \
        ClubDatabase.h \
        CreateGame.h \
        Fixture.h \
        GameMenu.h \
        League.h \
        MainWindow.h \
        Manager.h \
        Match.h \
        MatchEngine.h \
        Player.h \
        PlayerDatabase.h \
        Tactic.h

FORMS += \
        gamemenu.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
