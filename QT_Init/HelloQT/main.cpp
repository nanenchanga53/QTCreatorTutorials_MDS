#include "widget.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();
    return a.exec();
}
//C++과 비슷하지만 완전히 C++라이브러리를 갖는 언어가 아니라
//C++ 스타일의 언어이며 C++로 컴파일 하도록 자동으로 변환해주는 언어라 할 수 있다
