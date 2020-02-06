#ifndef IMU_WIDGET_H
#define IMU_WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Imu_Widget; }
QT_END_NAMESPACE

class QTcpSocket;
class imu3d;
class Imu_Widget : public QWidget
{
    Q_OBJECT

public:
    Imu_Widget(QWidget *parent = nullptr);
    ~Imu_Widget();

private:
    Ui::Imu_Widget *ui;
    void initialize();
    QTcpSocket *tcpSocket;
    imu3d* obj3d;




private slots:
    void connectButton();
    void readMessage();
    void disconnected();
};
#endif // Imu_Widget_H
