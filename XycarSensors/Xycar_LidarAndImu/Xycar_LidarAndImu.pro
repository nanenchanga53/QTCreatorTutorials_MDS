QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += /home/class/opencv-3.4.5/include

LIBS += -L/home/class/opencv-3.4.5/build/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera_widget.cpp \
    imu3d.cpp \
    lidar_widget.cpp \
    lidarpaint.cpp \
    main.cpp \
    imu_widget.cpp \
    sonar_widget.cpp

HEADERS += \
    camera_widget.h \
    imu3d.h \
    imu_widget.h \
    lidar_widget.h \
    lidarpaint.h \
    sonar_widget.h

FORMS += \
    camera_widget.ui \
    imu3d.ui \
    imu_widget.ui \
    lidar_widget.ui \
    lidarpaint.ui \
    sonar_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
