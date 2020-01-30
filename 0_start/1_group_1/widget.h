#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QCheckBox;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    QCheckBox *exclusive[2], *non_exclusive[2];
    QButtonGroup *chk_group[2];

    QString str1[3] = { "check1_&1", "check1_&2", "check1_&3" };
    QString str2[3] = { "check2_&1", "check2_&2", "check2_&3" };

public slots:
    void chkChanged(int id);
    void chkChanged_Non(int id);

};
#endif // WIDGET_H
