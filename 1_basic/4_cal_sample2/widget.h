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

private:
    QLabel* label;
    QString numberTemp;
    QString operate;

public slots:
    void setNum();
    void operation();
    void calculate();
    void clear();

    void clickedGroup(int id);
};
#endif // WIDGET_H



