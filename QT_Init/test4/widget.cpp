#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Memo");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "./untitled.txt", tr("text(*.txt)"));

    QFile data(fileName);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        out << ui->textEdit->toPlainText();
    }
    data.close();

    this->setWindowTitle(QFileInfo(data).fileName());
}

void Widget::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load File"), "./untitled.txt", tr("text(*.txt)"));

    QFile data(fileName);
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString instr;
        in >> instr;
        ui->textEdit->setText(instr);
    }
    data.close();

    this->setWindowTitle(QFileInfo(data).fileName());
}

void Widget::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
}

void Widget::on_textEdit_textChanged()
{
    ui->label->setText(QString("%1 %2").arg(QString::number((ui->textEdit->toPlainText().length()))).arg("count"));
}
