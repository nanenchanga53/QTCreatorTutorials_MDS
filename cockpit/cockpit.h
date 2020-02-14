#ifndef COCKPIT_H
#define COCKPIT_H

#include <QWidget>
#include "common.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Cockpit; }
QT_END_NAMESPACE

class QLCDNumber;
class imu3d;

class cockpit  : public QWidget
{
    Q_OBJECT

public:
    cockpit(QWidget *parent = nullptr);
    ~cockpit();

protected:
    void paintEvent(QPaintEvent *);


public:
    imu3d* obj_imu3d;
    int iRenderCnt;


    void initialize();

    // Image
    QPixmap* cluster_bg;
    QPixmap* arr_left;
    QPixmap* arr_right;

    QLCDNumber *lcd;

private:
    Ui::Cockpit *ui;


private slots:
    void displayClock();

    void recv_YPR(float, float, float);
};

#endif // COCKPIT_H
