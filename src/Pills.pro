#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T16:09:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pills
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    list.cpp \
    dialog.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    list.h \
    dialog.h \
    about.h

FORMS    += mainwindow.ui \
    dialog.ui \
    dialog.ui \
    dialog.ui \
    about.ui

DISTFILES += \
    ../../Downloads/capsule-black-and-white-variant (1).ico
win32:RC_ICONS += icon.ico


CONFIG += c++11

