#ifndef LIDARPAINT_H
#define LIDARPAINT_H

#include <QWidget>

#include <QBrush>
#include <QFont>
#include <QPen>

namespace Ui {
class LidarPaint;
}

class LidarPaint : public QWidget
{
    Q_OBJECT

public:
    explicit LidarPaint(QWidget *parent = nullptr);
    ~LidarPaint();

    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void drawPoint(int angle,int length);

private:
    Ui::LidarPaint *ui;
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
    int iDist[360];
    int startAngle;

public slots:
    void ChangeAngle(QString angle);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // LIDARPAINT_H
