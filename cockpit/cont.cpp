#include "cont.h"
#include "ui_cont.h"

#include "common.h"

cont::cont(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cont)
{
    ui->setupUi(this);

    connect(ui->end, SIGNAL(clicked()), qApp, SLOT(quit()));

    common::GetInstance().lidar_rad = ui->lidarrad->text().trimmed().toInt();
}

cont::~cont()
{
    delete ui;
}

void cont::connectDevice()
{
    emit connLidar(ui->carip->text().trimmed(), ui->lidarport->text().trimmed());
    emit connCam(ui->carip->text().trimmed(), ui->camport->text().trimmed());
    emit connImu(ui->carip->text().trimmed(), ui->sonarport->text().trimmed());
    emit connSonar(ui->carip->text().trimmed(), ui->imuport->text().trimmed());
}

void cont::disconnectDevice()
{
    emit disconn();
}

void cont::on_accel_clicked()
{
    if(common::GetInstance().iGear == 1 || common::GetInstance().iGear == 3)
    {
        if(common::GetInstance().iSpeed < 240)
        {
            common::GetInstance().iSpeed += 1;
        }
    }
}

void cont::on_brake_clicked()
{
    if(common::GetInstance().iSpeed > 0)
    {
        common::GetInstance().iSpeed -= 1;
    }
}

void cont::on_left_clicked()
{
    common::GetInstance().bRightOn = false;
    common::GetInstance().bLeftOn = !common::GetInstance().bLeftOn;
    if(common::GetInstance().bEmgrOn != true)
    {
        common::GetInstance().iL_On_DispCnt = 0;
    }
}

void cont::on_right_clicked()
{
    common::GetInstance().bLeftOn = false;
    common::GetInstance().bRightOn = !common::GetInstance().bRightOn;
    if(common::GetInstance().bEmgrOn != true)
    {
        common::GetInstance().iR_On_DispCnt = 0;
    }
}

void cont::on_emgr_clicked()
{
    common::GetInstance().bEmgrOn = !common::GetInstance().bEmgrOn;
    common::GetInstance().iL_On_DispCnt = 0;
    common::GetInstance().iR_On_DispCnt = 0;
}

void cont::on_gear_valueChanged(int value)
{
    common::GetInstance().iGear = value;
}

void cont::on_lidarrad_textChanged(const QString &arg1)
{
    common::GetInstance().lidar_rad = ui->lidarrad->text().trimmed().toInt();
}
