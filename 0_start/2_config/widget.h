#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QComboBox;
class QTextEdit;
class QLineEdit;
class QLabel;
class QLCDNumber;
class QProgressBar;
class QTextBrowser;
class QPushButton;
class QRadioButton;
class QCheckBox;
class QButtonGroup;
class QSlider;
class QScrollBar;
class QDial;
class QSlider;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    QComboBox *combo;
    QLineEdit *line;
    QLabel *label,*tempset,*temp,*volset,*isSliderPressed;
    QLCDNumber *lcd;
    QProgressBar *pbar;
    QTextBrowser *browser;
    QPushButton *btn;
    QRadioButton *radio[3];
    QCheckBox *check[3];
    QButtonGroup *btngroup;
    QSlider *slider;
    QScrollBar *scbar;
    QDial *dial;

public slots:
    void setValueSlider(int value);
    void setValueDial(int value);
    void setSliderPressedOn();
    void setSliderPressedOff();


};
#endif // WIDGET_H
