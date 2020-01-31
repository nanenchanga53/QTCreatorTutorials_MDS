#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;
class QTextEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    QLabel* label;

    QTextEdit *edit;

protected:
    void moveEvent(QMoveEvent*);

    bool eventFilter(QObject*, QEvent*);
};
#endif // WIDGET_H
