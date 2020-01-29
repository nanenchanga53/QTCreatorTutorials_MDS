#include "dialog.h"

#include <QColorDialog>
#include <QTextEdit>
#include <QPushButton>

#include <QFontDialog>

#include <QLineEdit>
#include <QInputDialog>
#include <QDebug>

dialog::dialog(QWidget *parent)
    : QDialog(parent)
{
    resize(500, 500);
    textedit = new QTextEdit(this);
    textedit->move(10, 50);
    QPushButton *btn = new QPushButton("OPEN COLOR", this);
    btn->move(10, 10);
    QPushButton *btn2 = new QPushButton("OPEN FONT", this);
    btn2->move(120, 10);
    QPushButton *btn3 = new QPushButton("OPEN INPUT", this);
    btn3->move(230, 10);

    connect(btn, SIGNAL(clicked()), this, SLOT(pushed_colorbtn()));
    connect(btn2, SIGNAL(clicked()), this, SLOT(pushed_fontbtn()));
    connect(btn3, SIGNAL(clicked()), this, SLOT(pushed_inputbtn()));
}

void dialog::pushed_colorbtn()
{
    QColor color = QColorDialog :: getColor(textedit->textColor(), this);
    textedit->setTextColor(color);
}

void dialog::pushed_fontbtn()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textedit->currentFont(), this) ;
    if (ok) textedit->setCurrentFont(font);
}

void dialog::pushed_inputbtn()
{
    bool ok;
    QString filename = QInputDialog :: getText(this, "Input Dialog", "Inpt File Name",
                                                         QLineEdit::Normal, "", &ok) ;
    qDebug() << filename;
}

