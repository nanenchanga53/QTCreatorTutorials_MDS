#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>
#include <QTcpSocket>

#include <iostream>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "lidar_widget.h"

namespace Ui {
class Camera_Widget;
}

class lidar_Widget;

class Camera_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Camera_Widget(QWidget *parent = nullptr,
            lidar_Widget* lidar = nullptr);
    ~Camera_Widget();

private:
    Ui::Camera_Widget *ui;
    void initialize();
    QTcpSocket *tcpSocket;
    QByteArray imgByte;
    cv::Mat img;
    lidar_Widget *ptr_lidar;

private slots:
    void connectButton(); // 연결 버튼
    void readMessage(); // 서버로부터 메세지를 받을 때 호출 됨
    void disconnected(); //서버와 연결이 종료했을때 슬롯
    void connetecd();

};

#endif // CAMERA_WIDGET_H
