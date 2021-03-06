#ifndef WIDGET_H
#define WIDGET_H

#include <QPushButton>
#include <QPropertyAnimation>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QPropertyAnimation *animation;

public slots:
    void btnClicked();

};

#endif // WIDGET_H
