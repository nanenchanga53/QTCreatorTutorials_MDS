#include "imu3d.h"
#include "ui_imu3d.h"
#include <QTimer>
#include <math.h>
#include <QPainter>

Imu3D::Imu3D(QWidget *parent) :  QOpenGLWidget(parent)
{
    ui->setupUi(this);
}

Imu3D::~Imu3D()
{
    delete ui;
}

void Imu3D::timerFunction()
{
    update(); //GL 업데이트
}


void Imu3D::initializeGL() //GL 초기화
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST); //깊이값 반영
}

void Imu3D::resizeGL(int w, int h) //위젯 크기 변했을때
{
    GLfloat aspectRatio; //화면 비율

    if(h==0)
        h=1;

    glViewport(0,0,w,h); //뷰포트 설정

    glMatrixMode(GL_PROJECTION); //행렬모드지정
    glLoadIdentity(); //좌표계 초기화

    aspectRatio=(GLfloat)w/(GLfloat)h; //화면비율 지정

    if(w<=h)
    {
        windowWidth=1;
        windowHeight=1/aspectRatio;
        glFrustum(-1.0,1.0,-windowHeight,windowHeight,5.0,300.0);//3D
    }
    else
    {
        windowWidth=1*aspectRatio;
        windowHeight=1;
        glFrustum(-windowWidth,windowWidth,-1.0,1.0,5.0,3000.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Imu3D::paintGL() //실제 그리는 함수
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //화면을 지워준다.

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-1500.0f); //move along z-axis// 카메라 이동

    glRotatef(xRot_P,1.0,0.0,0.0);
    glRotatef(yRot_Y,0.0,1.0,0.0);
    glRotatef(zRot_R,0.0,0.0,1.0);

    glLineWidth(10.0);
    glBegin(GL_LINE_LOOP);
        glColor3f(1.f,0.f,0.f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(-400.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0.f,1.f,0.f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, -400.0, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0.f,0.f,1.f);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, -400.0);
    glEnd();

    /* create 3D-Cube */
     glBegin(GL_QUADS); //사각형
        //front
        glColor3f(1.0,0.0,0.0);
        glVertex3f(101.0,51.0,101.0);
        glVertex3f(-101.0,51.0,101.0);
        glVertex3f(-101.0,-51.0,101.0);
        glVertex3f(101.0,-51.0,101.0);

        //back
        glColor3f(1.0,0.0,0.0);
        glVertex3f(101.0,51.0,-101.0);
        glVertex3f(-101.0,51.0,-101.0);
        glVertex3f(-101.0,-51.0,-101.0);
        glVertex3f(101.0,-51.0,-101.0);

        //top
        glColor3f(0.0,0.0,1.0);
        glVertex3f(-101.0,51.0,101.0);
        glVertex3f(101.0,51.0,101.0);
        glVertex3f(101.0,51.0,-101.0);
        glVertex3f(-101.0,51.0,-101.0);

        //bottom
        glColor3f(0.0,1.0,0.0);
        glVertex3f(101.0,-51.0,101.0);
        glVertex3f(101.0,-51.0,-101.0);
        glVertex3f(-101.0,-51.0,-101.0);
        glVertex3f(-101.0,-51.0,101.0);

        //right
        glColor3f(1.0,1.0,0.0);
        glVertex3f(101.0,51.0,101.0);
        glVertex3f(101.0,-51.0,101.0);
        glVertex3f(101.0,-51.0,-101.0);
        glVertex3f(101.0,51.0,-101.0);

        //left
        glColor3f(1.0,0.0,1.0);
        glVertex3f(-101.0,51.0,101.0);
        glVertex3f(-101.0,-51.0,101.0);
        glVertex3f(-101.0,-51.0,-101.0);
        glVertex3f(-101.0,51.0,-101.0);
    glEnd();

    glFlush();
}

static void qNormalizeAngle(int &angle)
{
     while (angle < 0)
         angle += 360 * 16;
     while (angle > 360 * 16)
         angle -= 360 * 16;
}


void Imu3D::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot_P) {
        xRot_P = angle;
    }
}

void Imu3D::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot_Y) {
        yRot_Y = angle;
    }
}

void Imu3D::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot_R) {
        zRot_R = angle;
    }
}

void Imu3D::setXYZRotation(float y, float p, float r)
{
    xRot_P = p;
    yRot_Y = y * -1;
    zRot_R = r * -1;
    //updateGL();
}


void Imu3D::mousePressEvent(QMouseEvent *event)
 {
     lastPos = event->pos();
 }

 void Imu3D::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

     if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot_P + 1 * dy);
         setYRotation(yRot_Y + 1 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot_P + 1 * dy);
         setZRotation(zRot_R + 1 * dx);
     }
     lastPos = event->pos();
}
