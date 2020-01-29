#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QStackedLayout>

//사용자 위젯 만드
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
