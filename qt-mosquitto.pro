#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T23:34:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-mosquitto
TEMPLATE = app

DEFINES += "WITH_THREADING"

CONFIG += C++11

#LIBS += -lmosquitto
#LIBS += -lmosquittopp

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    qtmosq.h

FORMS    += mainwindow.ui

MOSQDIR = /home/master/projects/mosquitto.git/trunk

INCLUDEPATH += $$MOSQDIR/lib \
    $$MOSQDIR/lib/cpp


# CPP
unix:!macx: LIBS += -L$$MOSQDIR/lib/cpp/ -lmosquittopp

INCLUDEPATH += $$MOSQDIR/lib/cpp
DEPENDPATH += $$MOSQDIR/lib/cpp

unix:!macx: PRE_TARGETDEPS += $$MOSQDIR/lib/cpp/libmosquittopp.a


# C
unix:!macx: LIBS += -L$$MOSQDIR/lib/ -lmosquitto

INCLUDEPATH += $$MOSQDIR
DEPENDPATH += $$MOSQDIR
INCLUDEPATH += $$MOSQDIR/lib
DEPENDPATH += $$MOSQDIR/lib

unix:!macx: PRE_TARGETDEPS += $$MOSQDIR/lib/libmosquitto.a


LIBS += -lcares
LIBS += -lssl
LIBS += -lcrypto
LIBS += -lpthread

