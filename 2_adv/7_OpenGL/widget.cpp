#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    resize(200, 200);
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(0.0f, 0.0);
        glColor3f(0.f, 1.f, 0.f);
        glVertex2f(0.5f, 0.5);
        glColor3f(0.f, 0.f, 1.f);
        glVertex2f(1.0f, 0.0);
    glEnd();

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.drawText(45, 120, "HI OPENGL");
    painter.end();

    glFlush();
}


void Widget::resizeGL(int w, int h)
{
    qDebug("W: %d, H: %d\n", w, h);
    glViewport(0, 0, (GLint)w/2, (GLint)h/2);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



