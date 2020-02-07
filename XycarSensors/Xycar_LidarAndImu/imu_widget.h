#ifndef IMU_WIDGET_H
#define IMU_WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class imu_widget; }
QT_END_NAMESPACE

class QTcpSocket;
class Imu3D;
class imu_widget : public QWidget
{
    Q_OBJECT

public:
    imu_widget(QWidget *parent = nullptr);
    ~imu_widget();

signals:
    void SendYaw(int numYaw);

private:
    Ui::imu_widget *ui;
    void initialize();
    QTcpSocket *tcpSocket;
    Imu3D* obj3d;

private slots:
    void connectButton();
    void readMessage();
    void disconnected();
};
#endif // IMU_WIDGET_H
