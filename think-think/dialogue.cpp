#include "dialogue.h"
#include "mywindow.h"

#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Dialogue::Dialogue(QWidget *parent, const QString &name)
    : QWidget{parent},
      dlgCount(0)
{
    QFile json(":/resources/dialogues/" + name + ".json");
    json.open(QIODevice::ReadOnly);
    doc = new QJsonDocument(QJsonDocument::fromJson(json.readAll()));

    prologue = new QLabel(this);
    prologue->setWordWrap(true);
    prologue->setAlignment(Qt::AlignCenter);
    prologue->setGeometry(200,600,2560-200*2,500);
    prologue->setStyleSheet("QLabel{font:50px}");
    QString str = doc->object().value("prologue").toString();
    prologue->setText(str);

    dlg = new QLabel(this);
    dlg->setWordWrap(true);
    dlg->setAlignment(Qt::AlignCenter);
    dlg->setGeometry(200,1440-500,2560-200*2,500);
    dlg->setStyleSheet("QLabel{font:50px}");

    QPushButton *button = new QPushButton(">>", this);
    button->move(2560-200,1440-200);
    button->setStyleSheet("QPushButton{font:50px;}");
    button->resize(200,200);
    button->setFlat(true);

    connect(button, &QPushButton::clicked,
            this, &Dialogue::handleButtonClick);
}

void Dialogue::handleButtonClick()
{
    prologue->setText("");
    if(dlgCount<doc->object().value("dialogue").toArray().size()){
        dlg->setText(doc->object().value("dialogue").toArray().at(dlgCount).toObject().value("content").toString());
        ++dlgCount;
    }
    else emit dialogueEnded();
}
