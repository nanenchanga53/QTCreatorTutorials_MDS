#include "imu_widget.h"
#include "lidar_widget.h"
#include "camera_widget.h"
#include "sonar_widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imu_widget w;
    lidar_Widget w2;
    Camera_Widget w3(nullptr, &w2);
    Sonar_Widget w4;
    w.show();
    w2.show();
    w3.show();
    w4.show();


    QObject::connect(&w,SIGNAL(SendYaw(int)),&w2,SLOT(recvYaw(int)));





    return a.exec();
}
