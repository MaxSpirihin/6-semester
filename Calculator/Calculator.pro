#-------------------------------------------------
#
# Project created by QtCreator 2016-02-19T18:49:56
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calculator.cpp

HEADERS  += mainwindow.h \
    calculator.h \
    main.h \
    interfaces.h

FORMS    += mainwindow.ui
