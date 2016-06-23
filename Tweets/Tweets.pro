#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T18:19:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Tweets
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    stemmer.cpp \
    tweetreader.cpp

HEADERS += \
    stemmer.h \
    tweetreader.h
