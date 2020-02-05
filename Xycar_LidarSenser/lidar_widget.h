#ifndef LIDAR_WIDGET_H
#define LIDAR_WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Lidar_Widget; }
QT_END_NAMESPACE

class QTcpSocket;
class imu3d;
class Lidar_Widget : public QWidget
{
    Q_OBJECT

public:
    Lidar_Widget(QWidget *parent = nullptr);
    ~Lidar_Widget();

private:
    Ui::Lidar_Widget *ui;
    void initialize();
    QTcpSocket *tcpSocket;

    imu3d* obj3d;


private slots:
    void connectButton();
    void readMessage();
    void disconnected();
};
#endif // LIDAR_WIDGET_H
