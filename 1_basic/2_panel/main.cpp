#include "widget.h"
#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dialog d;
    //d.show();
    d.exec();

    Widget w;
    w.show();
    return a.exec();
}
