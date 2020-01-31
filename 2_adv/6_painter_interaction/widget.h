#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int clipWidth;

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    void timerEvent(QTimerEvent*);

    void mouseMoveEvent(QMouseEvent *event);
};
#endif // WIDGET_H
