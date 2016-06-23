#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T13:24:46
#
#-------------------------------------------------

QT       += core gui
QT += phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        playerwindow.cpp \
    player.cpp \
    utils.cpp

HEADERS  += playerwindow.h \
    main.h \
    player.h \
    utils.h

FORMS    += playerwindow.ui
