#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>

class QTcpServer;
class QNetworkSession;

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
    QTcpServer *tcpServer;

private slots:
    void newConnection();
};

#endif // WIDGET_H
