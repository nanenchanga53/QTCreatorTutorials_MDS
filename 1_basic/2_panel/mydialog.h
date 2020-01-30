#ifndef MYDIALOG_H
#define MYDIALOG_H

#include<QDialog>

class myDialog : public QDialog
{
public:
    myDialog(QDialog *parent = nullptr);
    ~myDialog();

public slots:
    void pushed_Save2();
};

#endif // MYDIALOG_H
