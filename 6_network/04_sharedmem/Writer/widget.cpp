#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QBuffer>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->writeButton, &QPushButton::pressed,
            this, &Widget::writeButton);

    QString key = QString("shardmem");
    m_sharedMemory = new QSharedMemory(key);
}

void Widget::writeButton()
{
    if (m_sharedMemory->isAttached()) {
        if (!m_sharedMemory->detach())
            ui->label->setText(tr("Shhared memory detach 실패."));
    }


    QString fileName;
    fileName = QFileDialog::getOpenFileName(
                            0, QString(), QString(),
                            tr("Images (*.png *.xpm *.jpg)"));
    QImage image;
    if (!image.load(fileName)) {
        ui->label->setText(tr("이미지 파일을 선택해 주세요."));
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << image;
    int size = buffer.size();

    if (!m_sharedMemory->create(size)) {
        ui->label->setText(tr("Shared 메모리 Segment 생성 실패"));
        return;
    }
    m_sharedMemory->lock();
    char *to = (char*)m_sharedMemory->data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(m_sharedMemory->size(), size));
    m_sharedMemory->unlock();
}

Widget::~Widget()
{
    delete ui;
}
