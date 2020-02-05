#include "widget.h"
#include "ui_widget.h"

#include <QtXml>
#include <QtDebug>

void retrievElements(QDomElement root, QString tag)
{
    QDomNodeList nodes = root.elementsByTagName(tag);

    qDebug() << "노드의 개수 = " << nodes.count();
    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        if( elm.isElement() )
        {
          QDomElement element = elm.toElement();
          qDebug() << "ELEMENT" << element.tagName();
          qDebug() << "Element text: " << element.toElement().text();
        }

    }
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);    

    QDomDocument document;
    QFile file("../sample.xml");
    if(!file.open(QIODevice::ReadOnly
                  | QIODevice::Text)) {
        qDebug() << "Failed to open file.";
        return;
    } else {
        if(!document.setContent(&file)) {
            qDebug() << "Failed to reading.";
            return;
        }
        file.close();
    }

    QDomElement root =
            document.firstChildElement();

    retrievElements(root, "member");
    qDebug() << "Reading finished";
}

Widget::~Widget()
{
    delete ui;
}

