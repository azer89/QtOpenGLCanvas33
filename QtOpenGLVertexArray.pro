#-------------------------------------------------
#
# Project created by QtCreator 2015-02-21T17:40:06
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpenGLVertexArray
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GLContainer.cpp \
    GLWidget.cpp \
    stdafx.cpp

HEADERS  += mainwindow.h \
    GLContainer.h \
    GLWidget.h \
    MyPoint.h \
    stdafx.h

INCLUDEPATH += /home/azer/Qt5.3.2/5.3/gcc_64/include/QtOpenGL

FORMS    += mainwindow.ui

LIBS += -lglut -lGL -lGLU

CONFIG += console opengl thread precompile_header

PRECOMPILED_HEADER = stdafx.h



