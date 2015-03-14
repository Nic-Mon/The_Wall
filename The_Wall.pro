#-------------------------------------------------
#
# Project created by QtCreator 2015-03-12T17:55:43
#
#-------------------------------------------------

QT       += core gui \
            multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = The_Wall
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    youdied.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    youdied.h \
    gameboard.h

FORMS    += mainwindow.ui \
    youdied.ui \
    gameboard.ui \
    instructions.ui

RESOURCES += \
    rec.qrc
