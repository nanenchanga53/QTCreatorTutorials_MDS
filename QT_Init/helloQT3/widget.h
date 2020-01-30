#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void mQSpinBox();
    void mQSlider();
    void mQRadioButton();
    void mQDial();
};

#endif // WIDGET_H
