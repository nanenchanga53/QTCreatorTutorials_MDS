#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QTextEdit;

class dialog  : public QDialog
{
    Q_OBJECT
public:
    explicit dialog(QWidget *parent = nullptr);

public:
    QTextEdit *textedit;

signals:

public slots:
    void pushed_colorbtn();
    void pushed_fontbtn();
    void pushed_inputbtn();
};

#endif // DIALOG_H
