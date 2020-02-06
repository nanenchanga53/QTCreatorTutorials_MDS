#ifndef LIDAR_WIDGET_H
#define LIDAR_WIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Lidar_Widget; }
QT_END_NAMESPACE

class QTcpSocket;
class lidarPaint;
class Lidar_Widget : public QWidget
{
    Q_OBJECT

public:
    Lidar_Widget(QWidget *parent = nullptr);
    ~Lidar_Widget();
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    Ui::Lidar_Widget *ui;
    void initialize();
    QTcpSocket *tcpSocket;
    lidarPaint* objpaint;
    int iDist[360];



private slots:
    void connectButton();
    void readMessage();
    void disconnected();
};
#endif // LIDAR_WIDGET_H
