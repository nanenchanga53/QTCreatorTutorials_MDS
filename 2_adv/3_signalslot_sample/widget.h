#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void sigCustom(int);

public slots:
    void slotCustom(int);

    void slotExample();

    void emitSlot();
    void TargetSlot(int);
};
#endif // WIDGET_H
