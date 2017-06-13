#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T16:29:45
#
#-------------------------------------------------

QT       += core gui opengl multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trabalhoFinal3dImageProcessing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    fileoperationsfromresource.cpp \
    videosurface.cpp \
    mathutil.cpp \
    filterattributes.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    fileoperationsfromresource.h \
    videosurface.h \
    mathutil.h \
    filterattributes.h

FORMS    += mainwindow.ui

RESOURCES += \
    shaders.qrc

DISTFILES += \
    shader.frag \
    shader.vert \
    edge.frag \
    gaussianblur.frag \
    bloom.frag \
    gammacorrection.frag \
    filtermask.frag \
    wave.frag \
    negativo.frag
