#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QStackedLayout>


class myWidget : public QWidget
{
    Q_OBJECT

public:
    myWidget(QWidget *parent = nullptr);
    ~myWidget();

    QStackedLayout *StackedLayout;

public slots:
    void setPage1();
    void setPage2();
    void setPage3();
};
#endif // MYWIDGET_H
