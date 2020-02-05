#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    void initialize();
    QTcpSocket *tcpSocket;

private slots:
    void connectButton(); // 연결 버튼
    void readMessage(); // 서버로부터 메세지를 받을 때 호출 됨
    void disconnected(); //서버와 연결이 종료했을때 슬롯
};

#endif // WIDGET_H
