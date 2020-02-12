#ifndef SONAR_WIDGET_H
#define SONAR_WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QObject>
#include <QBrush>
#include <QFont>
#include <QPen>

namespace Ui {
class Sonar_Widget;
}

class Sonar_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Sonar_Widget(QWidget *parent = nullptr);
    ~Sonar_Widget();
    QTcpSocket *tcpSocket;

private:
    Ui::Sonar_Widget *ui;
    void initialize();
    int recvLen_cm;
    int recvLen;
    QString strMsg;

private slots:
    void connectButton(); // 연결 버튼
    void readMessage(); // 서버로부터 메세지를 받을 때 호출 됨
    void disconnected(); //서버와 연결이 종료했을때 슬롯
    void connetecd();


protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SONAR_WIDGET_H
