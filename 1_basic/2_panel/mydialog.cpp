#include "mydialog.h"
#include <QProgressDialog>
#include <QPushButton>
#include <QErrorMessage>

myDialog::myDialog(QDialog *parent) : QDialog(parent)
{
    QPushButton *btn = new QPushButton("SAVE", this);
    btn->move(10, 10);

    connect(btn, SIGNAL(clicked()), this, SLOT(pushed_Save2()));
}

myDialog::~myDialog()
{

}

void myDialog::pushed_Save2()
{
    int a = 1;
    QProgressDialog * processDlg = new QProgressDialog(this) ;
    processDlg->setRange(0, 99);
    processDlg->setValue(50);
    processDlg->exec();

    QErrorMessage *errorMsgDlg = new QErrorMessage(this);
    errorMsgDlg->showMessage("Error Message [FAILED]<br>"
                               "<font color=red>how do you do? <br>hello there!</font>");

    errorMsgDlg->exec();
}
