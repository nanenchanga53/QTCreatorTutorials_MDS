#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    m_duration = 0;

    ui->setupUi(this);
    connect(ui->volSlider, SIGNAL(valueChanged(int)),
            this, SLOT(sliderValueChange(int)));

    ui->sliderPosition->setEnabled(false);

    connect(ui->pbtOpen,  SIGNAL(clicked()),
            this,         SLOT(onOpenBtn()));
    connect(ui->pbtPlay,  SIGNAL(clicked()),
            this,         SLOT(onPlayBtn()));
    connect(ui->pbtPause, SIGNAL(clicked()),
            this,         SLOT(onPauseBtn()));
    connect(ui->pbtStop,  SIGNAL(clicked()),
            this,         SLOT(onStopBtn()));

    m_player = new QMediaPlayer();

    connect(m_player, &QMediaPlayer::durationChanged,
            this,     &Widget::durationChanged);

    connect(m_player, &QMediaPlayer::positionChanged,
            this,     &Widget::positionChanged);

    connect(ui->sliderPosition, &QSlider::sliderMoved,
            this,               &Widget::seek);

}

void Widget::sliderValueChange(int val)
{
    ui->labelVolume->setText(QString("%1").arg(val));
    m_player->setVolume(val);
}

void Widget::onOpenBtn()
{
    m_fName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"),
                                     QDir::homePath());
    if(!m_fName.isNull())
        ui->lblFileName->setText(m_fName);
}

void Widget::onPlayBtn()
{
    if(!m_fName.isNull())
    {
        m_player->setMedia(QUrl::fromLocalFile(m_fName));
        ui->sliderPosition->setEnabled(true);
        m_player->play();
    }
}

void Widget::onPauseBtn()
{
    int state = m_player->state();

    if(state == QMediaPlayer::PausedState)
    {
        m_player->play();
    }
    else if(state == QMediaPlayer::PlayingState)
    {
        m_player->pause();
    }
}

void Widget::onStopBtn()
{
    int state = m_player->state();

    if(state == QMediaPlayer::PlayingState)
    {
        m_player->stop();
    }
}

void Widget::durationChanged(qint64 duration)
{
    m_duration = duration / 1000;
    ui->sliderPosition->setMaximum(m_duration);
}

void Widget::positionChanged(qint64 progress)
{
    if (!ui->sliderPosition->isSliderDown())
        ui->sliderPosition->setValue(progress / 1000);

    qint64 currentInfo = progress / 1000;

    QString playTimeStr;
    if (currentInfo || m_duration) {
        QTime currentTime((currentInfo / 3600) % 60,
                          (currentInfo / 60) % 60,
                           currentInfo % 60,
                          (currentInfo * 1000) % 1000);

        QTime totalTime((m_duration / 3600) % 60,
                        (m_duration / 60) % 60,
                         m_duration % 60,
                        (m_duration * 1000) % 1000);

        QString format = "mm:ss";
        if (m_duration > 3600)
            format = "hh:mm:ss";
        playTimeStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }

    ui->labelPlayTime->setText(playTimeStr);
}

void Widget::seek(int seconds)
{
    m_player->setPosition(seconds * 1000);
}

Widget::~Widget()
{
    delete ui;
}



























