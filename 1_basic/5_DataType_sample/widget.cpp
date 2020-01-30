#include "widget.h"

#include <QDebug>

#include <QFile>

#include <QLinkedList>
#include <QStack>
#include <QQueue>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // #1 QString
    QString str = "12312.01";
    QString str2 = "4";
    qDebug() << str2.toInt();
    qDebug() << str.toFloat();
    qDebug("x=%.02f", str.toFloat());
    qDebug("x=%.02f", str.toDouble());
    qDebug() << QString("%1").arg(str.toShort());
    qDebug() << QString("%1 %2").arg(str.toInt()).arg(str.toDouble());
    qDebug() << "Types:" << QString("String") << QChar('x') << QRect(0, 10, 50, 40);

    float floati = str.toFloat();
    int inti = static_cast<int>(floati);
    qDebug() << floati;
    qDebug() << inti;


    // #2 QByteArray
    QByteArray ba;
    ba.resize(5);
    ba[0] = 0x3c;
    ba[1] = 0xb8;
    ba[2] = 0x64;
    ba[3] = 0x18;
    ba[4] = 0xca;
    for (int i = 0; i < ba.size(); ++i) {
        if (ba.at(i) >= 'a' && ba.at(i) <= 'f')
            qDebug() << "Found character in range [a-f]" << "\n" << i; // endl
    }

    // #3 QDataStream
    QFile file("file.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << QString("the answer is");   // serialize a string
    out << (qint32)42;        // serialize an integer
    file.close();

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);    // read the data serialized from the file
    QString file_str;
    qint32 a;
    in >> file_str >> a;

    qDebug() << file_str;
    qDebug() << a;

    // #4 QTextStream
    QFile data("output.txt");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7 << " textstream";
    }

    // #5 QList
    QList<QString> list = { "one", "two", "three" };
    for (int i = 0; i < list.size(); ++i) {
        if (list.at(i) == "two")
            qDebug() << "Found two at position " << i;
    }

    // #6 QLinkedList
    QLinkedList<QString> linklist;
    linklist << "one" << "two" << "three";
    linklist.append("four");
    while (!linklist.isEmpty())
        qDebug() << linklist.takeFirst();

    // #7 QVector
    QVector<int> vector(10);
    int *vectordata = vector.data();
    for (int i = 0; i < 10; ++i)
    {
        vectordata[i] = 2 * i;
        qDebug() << vectordata[i];
    }

    // #8 QSet
    QSet<QString> set;
    set << "a" << "b" << "b";
    qDebug() << set;

    // #9 QMap
    QMap<QString, int> map;
    map["one"] = 1;
    map["three"] = 3;
    map["seven"] = 7;
    qDebug() << map;

    // #10 QHash
    QHash<QString, int> hash;
    hash["one"] = 1;
    hash["three"] = 3;
    hash["seven"] = 7;
    qDebug() << hash;

    // # 11 QStack
    QStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    while (!stack.isEmpty())
     qDebug() << stack.pop();

    // # 12 QStack
    QQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    while (!queue.isEmpty())
        qDebug() << queue.dequeue();
}

Widget::~Widget()
{
}

