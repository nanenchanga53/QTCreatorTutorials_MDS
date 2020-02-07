#include "imu_widget.h"
#include "lidar_widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    imu_widget w;
    lidar_Widget w2;
    w.show();
    w2.show();

    QObject::connect(&w,SIGNAL(SendYaw(int)),&w2,SLOT(recvYaw(int)));

    return a.exec();
}
