#include <QApplication>

//1
#include <QLCDNumber>

//2
#include <QProgressBar>

//3
#include <QDebug>
#include <QTextBrowser>
#include <QUrl>
#include <QDir>

//4
#include <QPushButton>

//5
#include <QLineEdit>

//6
#include <QTextEdit>

//7
#include <QComboBox>

//8
#include <QRadioButton>
#include <QButtonGroup>

//10
#include <QSpinBox>

//11
#include <QSlider>
#include <QStyleFactory>

//12
#include <QDial>


int main(int argc, char * argv[])
{
    QApplication qApps(argc, argv);

    QPushButton *exit = new QPushButton("프로그램 종료");
    exit->move(0,0);
    exit->show();

    QObject::connect(exit, SIGNAL(clicked()), qApp, SLOT(quit()));

    //1 LCD ///////////////////////////////////////
    QLCDNumber *lcd = new QLCDNumber();
    lcd->setDecMode();
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->display(2020);
    lcd->show();

    //2 ProgBar ///////////////////////////////////////
    QProgressBar *Pbar = new QProgressBar();
    Pbar->setValue(24);
    //Pbar->setInvertedAppearance(true);
    Pbar->show();

    //3 Textbrowser ///////////////////////////////////////
    qDebug() << "실행폴더 경로: " << QCoreApplication::applicationDirPath();

    QUrl url("htmldisp.html");
    QTextBrowser *tbsr = new QTextBrowser();
    tbsr->setSource(url);
    tbsr->show();

    //4 응용 textbrowser ///////////////////////////////////////
    QTextBrowser *tbsr2 = new QTextBrowser();
    QPushButton *btn = new QPushButton("GO BACK", tbsr2);
    btn->move(40,40);
    QUrl url2("htmldisp.html");
    tbsr2->setSource(url2);
    tbsr2->show();

    QObject::connect(btn, SIGNAL(clicked()), tbsr2, SLOT(backward()));

    //5 Line Edit ///////////////////////////////////////
    QLineEdit *lineEdit = new QLineEdit();
    // lineEdit->setEchoMode(QlineEdit::Password);
    lineEdit->setInputMask("099");
    lineEdit->setPlaceholderText("input the password");
    lineEdit->show();

    // 6 Text Edit ///////////////////////////////////////
    QTextEdit *txt = new QTextEdit();
    txt->setText("Hello, world!");
    txt->append("Appending some text…");
    txt->show();

    // 7 ComboBox ///////////////////////////////////////
    QComboBox *comboBox = new QComboBox();
    comboBox->addItem("Item1");
    comboBox->addItem("Item2");
    comboBox->addItem("Item3");
    comboBox->setEditable(true);
    comboBox->show();

    // 8 radio  ///////////////////////////////////////
    QButtonGroup *buttonGroup = new QButtonGroup();
    QRadioButton *radioButton[4];
    for(int i = 0; i<4; i++) {
        QString str = QString("RadioButton %1").arg(i+1);
        radioButton[i] = new QRadioButton(str, txt);
        radioButton[i]->move(10, 50+20*i);
        buttonGroup->addButton(radioButton[i]);
        radioButton[i]->show();
    }
    txt->show();

    // 9 checkbox button group 응용
    // 예제 없음.

    // 10 SpinBox
    QSpinBox *sBox = new QSpinBox();
    sBox->setRange(0, 10);
    sBox->setWrapping(true);
    sBox->setSpecialValueText("Hi");
    sBox->show();

    //11 Slider
    QSlider *slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    slider->setTickPosition(QSlider::TicksAbove);
    slider->setStyle(QStyleFactory::create("Fusion"));
    slider->show();

    //12 QDial
    QDial *dial = new QDial();
    dial->setWrapping(false);
    dial->setNotchesVisible(true);
    dial->setNotchTarget(10);
    dial->setRange(0,100);
    dial->show();

    return qApps.exec();
}
