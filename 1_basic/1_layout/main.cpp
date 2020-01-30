#include "widget.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QPushButton *exit = new QPushButton("Exit");
    //exit->move(0,0);
    //exit->show();

    //QObject::connect(exit, SIGNAL(clicked()), qApp, SLOT(quit()));

    Widget w;
    w.show();
    return a.exec();
}
