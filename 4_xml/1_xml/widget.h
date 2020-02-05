#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QFile            *mReadFile;

private slots:
    void readButtonClicked();
};
#endif // WIDGET_H
