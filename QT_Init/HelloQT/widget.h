#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

//사용 위젯 만들기
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
