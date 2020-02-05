#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QtNetwork/QNetworkAccessManager>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    void httpPost();

    QNetworkReply *reply;
    QNetworkAccessManager qnam;

public slots:
    void replyFinished(QNetworkReply *pNetworkReply);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
