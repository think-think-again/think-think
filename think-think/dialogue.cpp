#include "dialogue.h"
#include "mywindow.h"

#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>

Dialogue::Dialogue(MyWindow *parent)
    : QWidget{(QWidget *)parent},
      window(parent)
{
    QFile json(":/resources/ljy.json");
    json.open(QIODevice::ReadOnly);
    doc = new QJsonDocument(QJsonDocument::fromJson(json.readAll()));

    QLabel *prologue = new QLabel(this);
    prologue->setWordWrap(true);
    prologue->setAlignment(Qt::AlignCenter);
    prologue->setGeometry(200,600,2560-200*2,500);
    prologue->setStyleSheet("QLabel{font:50px}");
    QString str = doc->object().value("prologue").toString();
    prologue->setText(str);


    QPushButton *but12 = new QPushButton("进入战斗",this);
    but12->move(2560-200,1440-200);
    but12->setStyleSheet("QPushButton{font:50px;}");
    but12->resize(200,200);
    but12->setFlat(true);
//    but12->hide();

//    QPushButton *but11 = new QPushButton(">>",this);
//    but11->move(2560-200,1440-200);
//    but11->setStyleSheet("QPushButton{font:50px;}");
//    but11->resize(200,200);
//    but11->setFlat(true);

//    QLabel *lab1 = new QLabel(this);
//    lab1->setWordWrap(true);
//    lab1->hide();
//    lab1->setAlignment(Qt::AlignCenter);
//    lab1->setGeometry(200,600,2560-200*2,500);
//    lab1->setStyleSheet("QLabel{font:50px}");
//    lab1->setText("一个平平无奇的周四下午\nAI引论CV小班课上");

    connect(but12, &QPushButton::clicked,
            parent, &MyWindow::startBattle);
}
