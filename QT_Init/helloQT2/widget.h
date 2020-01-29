#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    //메소드 추가
    void mQLabel();
    void mQPushButton();
    void mQLCDNumber();
    void mQProgressBar();
    void mQLineEdit();
    void mQTextBrowser();

    ~Widget();
//별도의 메소드나 위젯을 생상하려면 새로 추가한다
public slots:
    void slotEixt();


};

#endif // WIDGET_H
