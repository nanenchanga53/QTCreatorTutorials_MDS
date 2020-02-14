#include "cockpit.h"
#include "ui_cockpit.h"
#include "imu3d.h"

#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QLCDNumber>

cockpit::cockpit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Cockpit)
{
    ui->setupUi(this);

    initialize();
}


cockpit::~cockpit()
{
    delete ui;

    delete cluster_bg;
    delete arr_left;
    delete arr_right;
}

void cockpit::initialize()
{
    iRenderCnt = 0;
    // imu3d 추가
    obj_imu3d = new imu3d();
    obj_imu3d = new imu3d(ui->imu3d);
    obj_imu3d ->resize(ui->imu3d->width(), ui->imu3d->height());

    //화면 갱신
    QTimer *disptimer = new QTimer(this);
    connect(disptimer, SIGNAL(timeout()), SLOT(update()));
    disptimer->start(20);

    //시계
    QTimer *timer = new QTimer(this);
    lcd = new QLCDNumber(8, this);
    lcd->setGeometry(this->width() / 2 - 50, this->height() / 2 + 100, 100, 50);
    lcd->setFrameStyle(0);
    connect(timer, SIGNAL(timeout()), SLOT(displayClock()));
    lcd->display(QString("%1").arg(QTime::currentTime().toString()));
    timer->start(1000);

    // load image
    cluster_bg = new QPixmap(":/images/cluster_1.jpg");
    arr_left = new QPixmap(":/images/lArrow.PNG");
    arr_right = new QPixmap(":/images/rArrow.PNG");
}

void cockpit::displayClock(){

    lcd->display(QString("%1").arg(QTime::currentTime().toString()));
}

void cockpit::recv_YPR(float y, float p, float r){

    obj_imu3d->setXYZRotation(y, p, r);
}

static const QPoint Needle[3] = {
    QPoint(3, 8),
    QPoint(-3, 8),
    QPoint(0, -70)
};

void cockpit::paintEvent(QPaintEvent *)
{
    iRenderCnt++;

    if(iRenderCnt % 20 == 19 && common::GetInstance().iSpeed > 0)
    {
        common::GetInstance().iSpeed -= 1;
    }

    QPainter* painter = new QPainter(this);
    painter->drawPixmap(0, 0, *cluster_bg);
    painter->save();

    //속도계 바늘 설정

    QColor NeedleColor(255, 255, 255, 200);

    //원주: 300pixel로 가정.
    int side = 300;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(width()/6 +10, height()/2);

    painter->scale(side/200.0, side/200.0);

    painter->setPen(Qt::NoPen);
    painter->setBrush(NeedleColor);

    painter->rotate(-120);
    painter->rotate(common::GetInstance().iSpeed);

    painter->drawConvexPolygon(Needle, 3);

    painter->restore();
    painter->save();

    painter->translate(width()*5/6 - 10, height()/2);

    // CAM 표시
    if(common::GetInstance().bRightOn == true
       || common::GetInstance().bLeftOn == true)
    {
        QImage image( common::GetInstance().img.data,
                      common::GetInstance().img.cols,
                      common::GetInstance().img.rows,
                      static_cast<int>(common::GetInstance().img.step),
                      QImage::Format_RGB888 );

        QPixmap pixmap = QPixmap::fromImage(image);
        QRect clipRect(-100, -100, 200, 200);
        painter->setClipping(true);
        painter->setClipRect(clipRect);
        painter->drawPixmap(-pixmap.width() / 2, -pixmap.height() / 2,
                            pixmap);
        painter->setClipping(false);
    }

    // LIDAR 표시
    painter->setPen(QPen(Qt::green, 2));
    painter->drawLine(0, 0, 0, -50);
    painter->setPen(QPen(Qt::blue, 1));
    painter->drawArc(40 / -2, 40 / -2, 40, 40, 0, 360 * 16);
    painter->drawText(20, 20, "20cm");
    painter->drawArc(100 / -2, 100 / -2, 100, 100, 0, 360 * 16);
    painter->drawText(40, 40, "50cm");
    painter->drawArc(200 / -2, 200 / -2, 200, 200, 0, 360 * 16);
    painter->drawText(80, 80, "100cm");

    painter->rotate(common::GetInstance().imu_Yaw + common::GetInstance().lidar_rad);

    painter->setPen(QPen(Qt::blue, 5));
    painter->drawPoint(0, 0);

    painter->setPen(QPen(Qt::red, 5));
    for(int i=0; i<360; i++)
    {
        if(common::GetInstance().lidar_iDist[i] != 0)
        {
            if(common::GetInstance().lidar_iDist[i] / 10 > 140)
            {
                continue;
            }
            painter->drawPoint(common::GetInstance().lidar_iDist[i] / 10, 0); // 1cm단위 1px당 약 1mm
        }
        painter->rotate(-1);
    }

    painter->restore();
    painter->save();

    if(common::GetInstance().bLeftOn == true || common::GetInstance().bEmgrOn == true)
    {
        if(common::GetInstance().iL_On_DispCnt % 120 < 60)
        {
            painter->drawPixmap(0, 0, *arr_left);
        }
        common::GetInstance().iL_On_DispCnt++;
    }

    if(common::GetInstance().bRightOn == true || common::GetInstance().bEmgrOn == true)
    {
        if(common::GetInstance().iR_On_DispCnt % 120 < 60)
        {
            painter->drawPixmap(this->width() - 100, 0, *arr_right);
        }
        common::GetInstance().iR_On_DispCnt++;
    }

    painter->setFont(QFont("Arial", 30, 25));
    painter->setPen(Qt::white);
    QRect font_rect(310, 100, 220, 180);
    painter->drawText(font_rect, Qt::AlignCenter, common::GetInstance().strGear[common::GetInstance().iGear]);

    painter->restore();
    painter->end();
    delete painter;
}

/*
 *


    // The startAngle and spanAngle must be specified in 1/16th of a degree,
    // i.e. a full circle equals 5760 (16 * 360).
    // Positive values for the angles
    QPainter *painter = new QPainter(this);

    painter->translate(width()/2, ui->sensor->y() + 30);

    QRect rectangle(-150, -300 + 20, 300, 600);
    int startAngle = 5760 / 4 * -1 + 16 * 30 * -1;
    int spanAngle = 16 * 30 * 2;


    painter->setPen(QPen(Qt::blue, 1));
    painter->setBrush(QBrush(Qt::white));
    //painter->drawRect(rectangle);
    painter->drawPie(rectangle, startAngle, spanAngle);

    painter->setPen(QPen(Qt::blue, 10));
    painter->drawPoint(0, 0);

    // 152.2cm
    painter->setPen(QPen(Qt::red, 1));
    if(iUltraDist_cm > 152)
    {
        iUltraDist_cm = 152;
    }
    painter->drawLine(-150, iUltraDist_cm * 2 + 20, 150, iUltraDist_cm * 2 + 20);
    painter->drawText(50, 0, strMsg);
    QRect clipRect(-150, 20, 300, iUltraDist_cm * 2);
    painter->setClipping(true);
    painter->setClipRect(clipRect);
    painter->setBrush(QBrush(Qt::red));
    painter->drawPie(rectangle, startAngle, spanAngle);

    delete painter;

*/



