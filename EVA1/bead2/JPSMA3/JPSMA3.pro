#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T10:04:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JPSMA3
TEMPLATE = app


SOURCES += main.cpp\
        gamewindow.cpp \
    gamemanager.cpp

HEADERS  += gamewindow.h \
    gamemanager.h

DISTFILES += \
    images/1.jpg \
    images/2.jpg \
    images/3.jpg

RESOURCES += \
    images.qrc
