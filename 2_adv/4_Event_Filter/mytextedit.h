#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QWidget>
#include <QTextEdit>

class myTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    myTextEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent*);
};

#endif // MYTEXTEDIT_H
