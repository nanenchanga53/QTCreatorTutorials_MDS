#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include "video.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QString         m_fName;
    QMediaPlayer   *m_player;
    video          *m_videp;
    qint64          m_duration;

private slots:
    void onOpenBtn();
    void onPlayBtn();
    void onPauseBtn();
    void onStopBtn();

    void sliderValueChange(int val);

    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);

    void seek(int seconds);
};

#endif // WIDGET_H
