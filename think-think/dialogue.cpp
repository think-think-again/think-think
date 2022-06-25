#include "dialogue.h"
#include "mywindow.h"

#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QFontDatabase>

Dialogue::Dialogue(QObject *parent, const QString &name)
    : QGraphicsScene{parent},
      dlgCount(0),
      clicked(false)
{
    timer = new QTimer(this);

    QFile fontFile(":/resources/FZYanSJW_Zhun.TTF");
    fontFile.open(QIODevice::ReadOnly);
    int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    font.setFamilies(QFontDatabase::applicationFontFamilies(fontId));
    font.setPixelSize(50);

    QPixmap _background(":/resources/classroom1.jpg");
    _background = _background.scaled(2560, 1440, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(_background);
    background->setPos(-(_background.width()-2560)/2, -(_background.height()-1440)/2);
    addItem(background);

    QPixmap _backgroundMask(2560, 1440);
    _backgroundMask.fill(QColor(255, 255, 255, 160));
    backgroundMask = new QGraphicsPixmapItem(_backgroundMask);
    addItem(backgroundMask);

    QPixmap _dialogueBackground(":/resources/dialogue_background.png");
    dialogueBackground = new QGraphicsPixmapItem(_dialogueBackground);

    QFile json(":/resources/dialogues/" + name + ".json");
    json.open(QIODevice::ReadOnly);
    doc = new QJsonDocument(QJsonDocument::fromJson(json.readAll()));

    prologue = new QLabel();
    /*QGraphicsProxyWidget *prologueProxy = */addWidget(prologue);
    prologue->setWordWrap(true);
    prologue->setAlignment(Qt::AlignTop);
    prologue->setGeometry(400, 400, 2560-400*2, 500);
    prologue->setFont(font);
    prologue->setStyleSheet("QLabel{ background: transparent}");

    dlg = new QLabel();
    QGraphicsProxyWidget *dlgProxy = addWidget(dlg);
    dlgProxy->setZValue(1);
    dlg->setWordWrap(true);
    dlg->setAlignment(Qt::AlignTop);
    dlg->setGeometry(600,1440-385,2560-1000,385);
    dlg->setFont(font);
    dlg->setStyleSheet("QLabel{ background: transparent; color: white}");

    connect(timer, &QTimer::timeout,
            this, &Dialogue::updateLabel);
}

void Dialogue::initialize()
{
    QString str = doc->object().value("prologue").toString();
    setTextAnimation(prologue, str);
}

void Dialogue::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(!clicked){
        clicked = true;
        prologue->setText("");
        removeItem(backgroundMask);
        addItem(dialogueBackground);
    }
    if(dlgCount<doc->object().value("dialogue").toArray().size()){
        QString str = doc->object().value("dialogue").toArray().at(dlgCount).toObject().value("content").toString();
        setTextAnimation(dlg, str);
        ++dlgCount;
    }
    else emit dialogueEnded();
}

void Dialogue::setTextAnimation(QLabel *label, const QString &str)
{
    animationStr = str;
    animationLabel = label;
    animationProgress = 0;
    timer->start(200);
}


void Dialogue::updateLabel()
{
    if(animationProgress == animationStr.length()){
        return;
    }
    else{
        QString str = "<p style='line-height: 70px'>" + animationStr.left(++animationProgress) + "</p>";
        animationLabel->setText(str);
        timer->start(30);
    }
}
