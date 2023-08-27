TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += /usr/local/include /
               /usr/local/include/opencv
               /usr/local/include/opencv2



LIBS += /usr/local/lib/*.so.*


LIBS += `pkg-config --libs opencv` -lMVSDK

LIBS +=-lpthread
SOURCES += \
        Armor/ArmorBag.cpp \
        Armor/ArmorDetector.cpp \
        Armor/LightBag.cpp \
        Communication/CRC.cpp \
        Communication/serial.cpp \
        ImgProcessing/imgprocessing.cpp \
        Solver/AngleSolver.cpp \
        Start/start.cpp \
        Tool/SVM.cpp \
        main.cpp \
    Fu/FuDetect.cpp \
    Fu/FuPredict.cpp \
    CameraDriver/mvvideocapture.cpp

HEADERS += \
    Armor/Armor.h \
    Communication/serial.h \
    ImgProcessing/imgprocessing.h \
    Info/Info.h \
    Solver/Solver.h \
    Start/start.h \
    Fu/Fu.h \
    CameraDriver/cameraapi.h \
    CameraDriver/mvvideocapture.h










