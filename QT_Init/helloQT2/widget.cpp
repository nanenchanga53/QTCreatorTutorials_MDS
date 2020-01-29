#include "widget.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QProgressBar>
#include <QLineEdit>
#include <QUrl>
#include <QTextBrowser>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //최상당 위젯 크기 설정
    this->resize(400,400);

    mQLabel();
    mQPushButton();
    mQLCDNumber();
    mQProgressBar();
    mQLineEdit();
    mQTextBrowser();
}
Widget::~Widget()
{

}

//헤더에 미리 선언을 해놓고 사용
void Widget::slotEixt()
{
    qDebug("in function");
    qApp->quit();
}

void Widget::mQLabel()
{
    //부모 위젯 설정
    QLabel *label = new QLabel("abc",this); //abc 글자를 갖는 레이블을 this위젯 안에 생성

    label->resize(100,100);
    //label -> show();//좌상의 엄청 작게 뜰 것이다
}

void Widget::mQPushButton()
{
    QPushButton *push = new QPushButton("btn",this);
    push->resize(50,50);
    push->show();

    //푸시버튼에 클릭 이벤트 시그널이 발생하면 종료
    QObject::connect(push,SIGNAL(clicked()),this,SLOT(slotEixt()));
    //메인에서 쓰려면 아래와 같이 quit을 쓰자
    //QObject::connect(push,SIGNAL(clicked()),this,SLOT(quit()));
}

void Widget::mQLCDNumber()
{
    //LCD 형태로 숫자를 표시하기 위해 사용
    QLCDNumber *lcd = new QLCDNumber(10,this);//생성시 몇자리까지 입력할지 정한다
    lcd->setDecMode();
    lcd->setSegmentStyle(QLCDNumber::Flat);
    //lcd->setHexMode(); //16진수 모드
    lcd->display(2020); //기본 10진수
    lcd->setGeometry(50,50,100,100);
    //lcd->show();

}

void Widget::mQProgressBar()
{
    //프로그래스바
    QProgressBar *Pbar = new QProgressBar(this);
    Pbar->setValue(24); //24%
    //Pbar->setInvertedAppearance(true); //역방향
    Pbar->setGeometry(50,150,300,100);
    Pbar->setTextVisible(true); //퍼센트 표시
    //Pbar->show();
}

// 입력 텍스트
void Widget::mQLineEdit()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setInputMask("099");
    lineEdit->setPlaceholderText("input the password");
    lineEdit->setGeometry(50,250,100,50);

}

//브라우저 불러오기(HTML)
void Widget::mQTextBrowser()
{
    QUrl url("qrc:/index.html"); //리소스로 설정해 높으면 이런 경로를 사용할 수 있다
    //QUrl url("index.html");
    QTextBrowser *tbsr = new QTextBrowser();
    tbsr->setSource(url);
    tbsr->show();
}
