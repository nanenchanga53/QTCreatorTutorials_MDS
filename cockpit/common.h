#ifndef COMMON_H
#define COMMON_H

#include <QString>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class common
{
public:
    common() {
        strGear[0] = "P";
        strGear[1] = "R";
        strGear[2] = "N";
        strGear[3] = "D";
    }

public:
    int iSpeed;
    bool bLeftOn;
    bool bRightOn;
    bool bEmgrOn;
    int iL_On_DispCnt;
    int iR_On_DispCnt;

    int lidar_rad;
    int lidar_iDist[360];

    int imu_Yaw;
    int iSonarDist_in;
    int iSonarDist_cm;

    int iGear;
    QString strGear[4];

    QByteArray imgbyte;
    cv::Mat img;

public:
    // Will initialize instance if needed
    static common &GetInstance(){
       static common instance;
       return instance;
    }
};

#endif // COMMON_H
