#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QLabel* label;

public slots:
    void displayClock();

protected:
    void timerEvent(QTimerEvent*);
};
#endif // WIDGET_H
