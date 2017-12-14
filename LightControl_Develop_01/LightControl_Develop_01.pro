#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T10:24:36
#
#-------------------------------------------------

QT += core gui
QT += serialport
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LightControl_Develop_01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\OpenCV\include"

LIBS += -L"C:\OpenCV\lib"\
        -llibopencv_core300\
        -llibopencv_imgproc300\
        -llibopencv_imgcodecs300\
        -llibopencv_highgui300\
        -llibopencv_videoio300
