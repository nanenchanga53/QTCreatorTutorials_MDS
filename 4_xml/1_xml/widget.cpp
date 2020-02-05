#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QXmlStreamReader>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::pressed,
            this,           &Widget::readButtonClicked);

    mReadFile = new QFile();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readButtonClicked()
{
    QString fName = QFileDialog::getOpenFileName(this,
                                                 "Open XML File",
                                                 QDir::currentPath(),
                                                 "XML Files (*.xml)");
    mReadFile->setFileName(fName);

    if(!QFile::exists(fName)) {
        ui->textEdit->setText("파일이 존재하지 않습니다. ");
        return;
    }

    if(!mReadFile->open(QIODevice::ReadOnly)) {
        ui->textEdit->setText("파일 Open 실패.");
        return;
    }

    QXmlStreamReader reader(mReadFile);

    QList<QString> members;


    QString inputData;
    while(!reader.atEnd())
    {
        reader.readNext();
        if(!reader.text().isEmpty()) {
            QString data = reader.text().toString();
            data.replace('\n', "");
            data.replace('\t', "");

            if(data.length() > 0)
                inputData.append(data).append("<br>");
        }
    }

    ui->textEdit->setText(inputData);
    reader.clear();
    mReadFile->close();


    QList<QString>   mOriData;

    mOriData.append("CMW");
    mOriData.append("rnd");

    mOriData.append("KMS");
    mOriData.append("intra");

    mOriData.append("KSJ");
    mOriData.append("operation");

    QFile writefile("output.xml");
    writefile.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&writefile);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Qt");
    for(int i = 0 ; i < mOriData.count() ; i+=2)
    {
        xmlWriter.writeStartElement("Info");
        xmlWriter.writeTextElement("Name", mOriData.at(i));
        xmlWriter.writeTextElement("Team",  mOriData.at(1));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    writefile.close();
}
