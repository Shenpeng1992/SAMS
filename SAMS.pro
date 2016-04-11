#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T12:18:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SAMS
TEMPLATE = app

include(../SAMS_Demo/SAMS.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    SAMFileDock.cpp \
    SAMCore.cpp \
    SAMInfoDock.cpp \
    SAMImgViewer.cpp \
    SAMPaintWidget.cpp \
    TerrainSub/DataStyle.cpp \
    TerrainSub/Matrix.cpp \
    SAMTerrianThread.cpp \
    SAMProductViewer.cpp \
    glwiget.cpp

HEADERS  += mainwindow.h \
    SAMFileDock.h \
    SAMCore.h \
    SAMInfoDock.h \
    SAMImgViewer.h \
    SAMPaintWidget.h \
    TerrainSub/DataStyle.h \
    TerrainSub/matcher.h \
    TerrainSub/Matrix.h \
    SAMTerrianThread.h \
    SAMProductViewer.h \
    glwiget.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc

DISTFILES +=

RC_FILE = \
  appIcon.rc
