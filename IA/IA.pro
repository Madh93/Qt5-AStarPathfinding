#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T18:44:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    pixmap.cpp \
    robot.cpp

HEADERS  += mainwindow.hpp \
    scene.hpp \
    pixmap.hpp \
    robot.hpp

FORMS    += mainwindow.ui
