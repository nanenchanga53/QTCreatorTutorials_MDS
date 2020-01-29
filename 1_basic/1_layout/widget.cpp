#include "widget.h"

// 1
#include <QHBoxLayout>
#include <QPushButton>

// 2
#include <QVBoxLayout>

// 4
#include <QGridLayout>
#include <QString>
#define NO_OF_ROW 3

// 5
#include <QDial>
#include <QLabel>
#include <QCalendarWidget>
#include <QTextEdit>
#include <QStackedLayout>

// 6
#include <QFrame>

// 7
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QTabWidget>

// 8
#include <QSplitter>


Widget::Widget(QWidget *parent):QWidget(parent)
{
    resize(600, 600);
   // 1 H Layout
    QPushButton *pushButton1 = new QPushButton();
    pushButton1->setText("Button1");
    QPushButton *pushButton2=new QPushButton("Button2");
    QPushButton *pushButton3=new QPushButton("Button3"); //QPushButton *pushButton3=new QPushButton("Button3",this);

    QHBoxLayout*hBoxLayout = new QHBoxLayout ;
    hBoxLayout->setMargin(0) ;
    hBoxLayout->addWidget(pushButton1);
    hBoxLayout->addWidget(pushButton2);
    hBoxLayout->addWidget(pushButton3);
    //setLayout(hBoxLayout);

    // 2 V Layout
    QPushButton *pushButton4 = new QPushButton();
    pushButton4->setText("Button4");
    QPushButton *pushButton5 = new QPushButton("Button5");
    QPushButton *pushButton6 = new QPushButton("Button6"); //QPushButton *pushButton6 = new QPushButton("Button6",this);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(); //또는 QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setMargin(6) ;
    vBoxLayout->addWidget(pushButton4);
    vBoxLayout->addWidget(pushButton5);
    vBoxLayout->addWidget(pushButton6);

    //setLayout(vBoxLayout);

    // 3 중첩 Layout
    QVBoxLayout *MultiLayer = new QVBoxLayout();
    MultiLayer->addLayout(hBoxLayout);
    MultiLayer->addLayout(vBoxLayout);
    //setLayout(MultiLayer);

    // 4 Grid
    QGridLayout *gridLayout = new QGridLayout;
    QPushButton *pushButton[NO_OF_ROW * NO_OF_ROW];
    for(int y = 0 ; y <NO_OF_ROW; y++) {
      for(int x = 0 ; x <NO_OF_ROW; x++) {
         QString str = QString("Button%1").arg(1+x+y*NO_OF_ROW);
         pushButton[x+y*NO_OF_ROW]=new  QPushButton(str); //pushButton[x+y*NO_OF_ROW]=new QPushButton(str, this);
         gridLayout->addWidget(pushButton[x+y*NO_OF_ROW],x,y);
      }
    }
    //setLayout(gridLayout);

    // 5 Calendar
    QDial *dial = new QDial(this);
    dial->setRange(0, 2);

    QLabel *label = new QLabel("Stack 1" , this) ;
    QCalendarWidget* calendarWidget = new QCalendarWidget(this);
    QTextEdit*textEdit = new QTextEdit("Stack 3" , this) ;

    QStackedLayout *stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(label);
    stackedLayout->addWidget(calendarWidget);
    stackedLayout->addWidget(textEdit);

    connect(dial, SIGNAL(valueChanged(int)), stackedLayout, SLOT(setCurrentIndex(int)));

    QHBoxLayout *hBoxStackLayout = new QHBoxLayout();
    hBoxStackLayout->addWidget(dial);
    hBoxStackLayout->addLayout(stackedLayout);

    //setLayout(hBoxStackLayout);

    // 6 Frame
    QFrame *plainline = new QFrame(this);
    plainline->setGeometry(QRect(0,0,270,16));
    plainline->setLineWidth(2);
    plainline->setFrameStyle(QFrame ::Plain);

    QFrame * raisedLine = new QFrame(this);
    raisedLine->setGeometry(QRect(0,10,270,16));
    raisedLine->setLineWidth(2);
    raisedLine->setFrameStyle(QFrame::HLine|QFrame::Raised);

    QFrame* sunkenLine = new QFrame(this);
    sunkenLine->setGeometry(QRect(0,20,270,16));

    sunkenLine->setLineWidth(2) ;
    sunkenLine->setFrameStyle(QFrame::HLine|QFrame::Sunken);

    // 7 GroupBox
    QLineEdit *lineEdit[3];
    for(int i = 0; i  <3; i++) {
        lineEdit[i] = new QLineEdit(this);
    }

    QFormLayout * formLayout = new QFormLayout ;
    formLayout->addRow("&IP Address", lineEdit[0]);
    formLayout->addRow("Mac Address" , lineEdit[1]);
    formLayout->addRow("&Date", lineEdit[2]);

    QGroupBox * groupBox = new QGroupBox("&Widget Group", this);
    groupBox->move(105, 105) ;
    groupBox->setLayout(formLayout) ;

    //resize( groupBox->sizeHint().width()+10,
    //        groupBox->sizeHint().height()+10);

    // 8 Tab
    QDial*  dial2 = new QDial(this) ;
    QCalendarWidget* calendarWidget2 = new QCalendarWidget(this);
    QTextEdit* textEdit2 = new QTextEdit("Tab 3", this);

    QTabWidget * tabWidget = new QTabWidget(this);
    tabWidget->addTab(dial2, "Tab 1");
    tabWidget->addTab(calendarWidget2, "Tab 2");
    tabWidget->addTab(textEdit2, "Tab 3");

    tabWidget->move(10, 200);

    // 9 Splitter
    QLabel  * label3= new QLabel ("IP Address" , this) ;
    QDial * dial3 = new QDial(this) ;

    QSplitter * splitter = new QSplitter(this) ;
    splitter->addWidget(label3);
    splitter->addWidget(dial3) ;


    splitter->move(10, 450);
}

Widget::~Widget()
{
}

