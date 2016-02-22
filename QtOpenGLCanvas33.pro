#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T16:55:48
#
#-------------------------------------------------

QT       += core gui opengl svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpenGLCanvas33
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           GLWidget.cpp \
           VertexDataHelper.cpp \
           SystemParams.cpp \
           GLContainer.cpp

HEADERS  += mainwindow.h \
            ALine.h \
            AVector.h \
            GLContainer.h \
            GLWidget.h \
            VertexData.h \
            VertexDataHelper.h \
            SystemParams.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -frounding-math -O3

QMAKE_CXXFLAGS += -std=gnu++1y

RESOURCES += \
    resources.qrc
