#include "widget.h"
#include "dialog.h"
#include "mydialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dialog d;
    d.show();
    d.exec();


    //myDialog my;
    //my.exec();


    //Widget w,w2;
    //w.show();
    //w2.show();


    return a.exec();
}
