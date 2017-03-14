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
        mainwindow.cpp \
    Subscribers.cpp \
    guarded.cpp \
    lr_guarded.cpp

HEADERS  += mainwindow.h \
    qtmosq.h \
    Subscribers.h \
    guarded.h \
    lr_guarded.h

FORMS    += mainwindow.ui

PLF = /mnt/data/projects/P1/P1/Source/Common/PLF

INCLUDEPATH += $$PWD/../../Mosquitto/mosquitto.git/trunk/lib \
               $$PWD/../../P1/P1/Source/Common/PLF/OS \
               $$PWD/../../P1/P1/Source/Common/PLF/PLIB/Exception \
#               $$PWD/../../P1/P1/Source/Common/PLF/PLIB/String \
               $$PLF/PLIB/String \
               /mnt/data/projects/P1/P1/Source/Common/PLF \
               /mnt/data/projects/P1/P1/Source/Common/PLF/TDD \
               /mnt/data/projects/P1/P1/Source/Common/PLF/PLIB/CuteUnitTest/cute_lib
#    $$PWD/../../Mosquitto/mosquitto.git/trunk/lib/cpp



# CPP
unix:!macx: LIBS += -L$$PWD/../../Mosquitto/mosquitto.git/trunk/lib/cpp/ -lmosquittopp

INCLUDEPATH += $$PWD/../../Mosquitto/mosquitto.git/trunk/lib/cpp
DEPENDPATH += $$PWD/../../Mosquitto/mosquitto.git/trunk/lib/cpp

unix:!macx: PRE_TARGETDEPS += $$PWD/../../Mosquitto/mosquitto.git/trunk/lib/cpp/libmosquittopp.a


# C
unix:!macx: LIBS += -L$$PWD/../../Mosquitto/mosquitto.git/trunk/lib/ -lmosquitto

INCLUDEPATH += $$PWD/../../Mosquitto/mosquitto.git/trunk
DEPENDPATH += $$PWD/../../Mosquitto/mosquitto.git/trunk
INCLUDEPATH += $$PWD/../../Mosquitto/mosquitto.git/trunk/lib
DEPENDPATH += $$PWD/../../Mosquitto/mosquitto.git/trunk/lib

unix:!macx: PRE_TARGETDEPS += $$PWD/../../Mosquitto/mosquitto.git/trunk/lib/libmosquitto.a


LIBS += -lcares
LIBS += -lssl
LIBS += -lcrypto
LIBS += -lpthread

