#ifndef VIDEO_H
#define VIDEO_H

#include <QVideoWidget>

class video : public QVideoWidget
{
    Q_OBJECT

public:
    explicit video(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // VIDEO_H
