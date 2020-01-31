#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QDir;
class QListWidget;
class QLineEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QDir *directory;
    QListWidget *dirListWidget;
    QLineEdit* filenameLineEdit;

    void refreshDir();

public slots:
    void selectItem();
    void changeDir();

    void makeDir();
    void removeDir();
    void renameDir();

};
#endif // WIDGET_H
