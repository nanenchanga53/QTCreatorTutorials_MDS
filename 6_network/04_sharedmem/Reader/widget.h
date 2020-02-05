#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSharedMemory>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QSharedMemory *m_sharedMemory;

private slots:
    void readButton();
};

#endif // WIDGET_H
