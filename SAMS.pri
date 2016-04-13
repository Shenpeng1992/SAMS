QT                        += core gui opengl
#################################################
#定义文件输出目录
BIN_PATH = $$PWD/../bin
LIB_PATH = $$PWD/../lib
INC_PATH = $$PWD/../include

DESTDIR = $$BIN_PATH

#include
INCLUDEPATH +=  $$INC_PATH
INCLUDEPATH +=  $$INC_PATH/opencv
INCLUDEPATH +=  $$INC_PATH/opencv2
INCLUDEPATH +=  $$F:/3rd_Library/glut/include

#设定LIB和bin
contains(QT_ARCH,i386){
    message("win32-x86 build")

    win32-msvc2013{
        LIB_PATH            =    $$LIB_PATH/VC12_x86
        BIN_PATH            =    $$BIN_PATH
    }
}else{#x64
    message("win32-x64 build")

    win32-msvc2013{
        LIB_PATH            =    $$LIB_PATH/VC12_x64
        BIN_PATH            =    $$BIN_PATH
    }
}
#################################################
#LIBS
win32-g++{
     CONFIG(debug, debug|release) {
        message(Building $$TARGET with G++ WIN32 DEBUG mode.)
    }else{
        message(Building $$TARGET with  G++ WIN32 RELEASE mode.)
    }
 }else{#MSVC
     CONFIG(debug, debug|release) {
        message(Building $$TARGET with MSVS WIN32 DEBUG mode.)
        LIBS += $$LIB_PATH/opencv_calib3d2410d.lib
        LIBS += $$LIB_PATH/opencv_contrib2410d.lib
        LIBS += $$LIB_PATH/opencv_core2410d.lib
        LIBS += $$LIB_PATH/opencv_features2d2410d.lib
        LIBS += $$LIB_PATH/opencv_flann2410d.lib
        LIBS += $$LIB_PATH/opencv_gpu2410d.lib
        LIBS += $$LIB_PATH/opencv_highgui2410d.lib
        LIBS += $$LIB_PATH/opencv_imgproc2410d.lib
        LIBS += $$LIB_PATH/opencv_legacy2410d.lib
        LIBS += $$LIB_PATH/opencv_ml2410d.lib
        LIBS += $$LIB_PATH/opencv_objdetect2410d.lib
        LIBS += $$LIB_PATH/opencv_ts2410d.lib
        LIBS += $$LIB_PATH/opencv_video2410d.lib
        LIBS += $$LIB_PATH/opencv_nonfree2410d.lib
        LIBS += $$LIB_PATH/glut.lib
        LIBS += $$LIB_PATH/glut32.lib
        SUFFIX_STR =d
    }else{
        message(Building $$TARGET with MSVS WIN32 RELEASE mode.)
        LIBS += $$LIB_PATH/opencv_calib3d2410.lib
        LIBS += $$LIB_PATH/opencv_contrib2410.lib
        LIBS += $$LIB_PATH/opencv_core2410.lib
        LIBS += $$LIB_PATH/opencv_features2d2410.lib
        LIBS += $$LIB_PATH/opencv_flann2410.lib
        LIBS += $$LIB_PATH/opencv_gpu2410.lib
        LIBS += $$LIB_PATH/opencv_highgui2410.lib
        LIBS += $$LIB_PATH/opencv_imgproc2410.lib
        LIBS += $$LIB_PATH/opencv_legacy2410.lib
        LIBS += $$LIB_PATH/opencv_ml2410.lib
        LIBS += $$LIB_PATH/opencv_objdetect2410.lib
        LIBS += $$LIB_PATH/opencv_ts2410.lib
        LIBS += $$LIB_PATH/opencv_video2410.lib
        LIBS += $$LIB_PATH/opencv_nonfree2410.lib
        LIBS += $$LIB_PATH/glut.lib
        LIBS += $$LIB_PATH/glut32.lib
    }
}

TARGET              = $$TARGET$$SUFFIX_STR
