#ifndef LIDARPAINT_H
#define LIDARPAINT_H

#include <QWidget>

#include <QBrush>
#include <QFont>
#include <QPen>

namespace Ui {
class lidarPaint;
}

class lidarPaint : public QWidget
{
    Q_OBJECT

public:
    explicit lidarPaint(QWidget *parent = nullptr);
    ~lidarPaint();

    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void drawPoint(int angle,int length);

private:
    Ui::lidarPaint *ui;
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;


protected:
    void paintEvent(QPaintEvent *event);
};

#endif // LIDARPAINT_H
