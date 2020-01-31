#include "widget.h"

#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir(".");
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    QPushButton *makeDir = new QPushButton("Make Dir", this);
    QPushButton *removeDir = new QPushButton("remove Dir", this);
    QPushButton *renameDir = new QPushButton("rename Dir", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(makeDir);
    layout->addWidget(removeDir);
    layout->addWidget(renameDir);

    connect(dirListWidget, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(selectItem()));
    connect(dirListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(changeDir()));
    connect(makeDir, SIGNAL(clicked()), SLOT(makeDir()));
    connect(removeDir, SIGNAL(clicked()), SLOT(removeDir()));
    connect(renameDir, SIGNAL(clicked()), SLOT(renameDir()));

    refreshDir();

}

Widget::~Widget()
{
}

//파일 리스트 불러오기
void Widget::refreshDir()
{
    dirListWidget->clear();
    for(int i=0; i<directory->entryList().count(); i++)
    {
        dirListWidget->addItem(directory->entryList().at(i));
    }
}

//파일을 선택해서 이름 가져오기
void Widget::selectItem()
{
    filenameLineEdit->setText(dirListWidget->currentItem()->text());
}

//디렉토리 변경
void Widget::changeDir()
{
    QFileInfo checkDir(dirListWidget->currentItem()->text());
    if(checkDir.isDir())
    {
        directory->cd(dirListWidget->currentItem()->text());
        refreshDir();
    }
}

//폴더생성
void Widget::makeDir()
{
    if(filenameLineEdit->text().length())
    {
        directory->mkdir(filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

//삭제
void Widget::removeDir()
{
    if(filenameLineEdit->text().length())
    {
        directory->rmdir(filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

//이름바꾸기
void Widget::renameDir()
{
    if(filenameLineEdit->text().length())
    {
        directory->rename(dirListWidget->currentItem()->text(), filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

