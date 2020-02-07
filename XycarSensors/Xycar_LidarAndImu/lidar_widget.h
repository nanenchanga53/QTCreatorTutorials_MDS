#ifndef LIDAR_WIDGET_H
#define LIDAR_WIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class lidar_Widget;
}

class QTcpSocket;
class LidarPaint;
class lidar_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit lidar_Widget(QWidget *parent = nullptr);
    ~lidar_Widget();
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

public slots:
    void recvYaw(int numYaw);

private:
    Ui::lidar_Widget *ui;
    void initialize();
    QTcpSocket *tcpSocket;
    LidarPaint* objpaint;
    int iDist[360];

private slots:
    void connectButton();
    void readMessage();
    void disconnected();

};

#endif // LIDAR_WIDGET_H
