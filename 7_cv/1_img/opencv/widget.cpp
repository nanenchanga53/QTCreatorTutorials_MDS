#include "widget.h"
#include "ui_widget.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    cv::Mat img = cv::imread("../opencv/1.jpg");
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", img);
    cv::waitKey(0);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::btnclick()
{
}

