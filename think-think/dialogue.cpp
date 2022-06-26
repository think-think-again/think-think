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

    QPixmap _dialogueBackground(":/resources/dialogue.png");
    _dialogueBackground = _dialogueBackground.scaled(2560, 1440);
    dialogueBackground = new QGraphicsPixmapItem(_dialogueBackground);
    addItem(dialogueBackground);
    dialogueBackground->hide();

    QPixmap _dialogueBackgroundBoss(":/resources/dialogue-1.png");
    _dialogueBackgroundBoss = _dialogueBackgroundBoss.scaled(2560, 1440);
    dialogueBackgroundBoss = new QGraphicsPixmapItem(_dialogueBackgroundBoss);
    addItem(dialogueBackgroundBoss);
    dialogueBackgroundBoss->hide();

    QPixmap _dialogueBackgroundZ(":/resources/dialogue-4.png");
    _dialogueBackgroundZ = _dialogueBackgroundZ.scaled(2560, 1440);
    dialogueBackgroundZ = new QGraphicsPixmapItem(_dialogueBackgroundZ);
    addItem(dialogueBackgroundZ);
    dialogueBackgroundZ->hide();

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
    dlg->setGeometry(700,1440-372,2560-1000,372);
    dlg->setFont(font);
    dlg->setStyleSheet("QLabel{ background: transparent; color: white}");

    speaker = new QLabel();
    addWidget(speaker);
    speaker->setAlignment(Qt::AlignTop);
    speaker->setGeometry(500,1440-180,2560-1000,180);
    speaker->setFont(font);
    speaker->setStyleSheet("QLabel{ background: transparent; color: #FFD700}");

    connect(timer, &QTimer::timeout,
            this, &Dialogue::updateLabel);
}

void Dialogue::initialize()
{
    QString str = doc->object().value("prologue").toString();
    setTextAnimation(prologue, str);
}

void Dialogue::mousePressEvent(__attribute__ ((unused))QGraphicsSceneMouseEvent *mouseEvent)
{
    if(!clicked){
        clicked = true;
        prologue->setText("");
        removeItem(backgroundMask);
    }
    if(dlgCount<doc->object().value("dialogue").toArray().size()){
        dialogueBackground->hide();
        dialogueBackgroundBoss->hide();
        dialogueBackgroundZ->hide();
        QString speakerName = doc->object().value("dialogue").toArray().at(dlgCount).toObject().value("speaker").toString();
        if(speakerName == "Voice-over"){
            dialogueBackground->show();
            speaker->setText("");
        }
        if(speakerName == "Boss"){
            dialogueBackgroundBoss->show();
            speaker->setText("刘老师");
        }
        if(speakerName == "小Z"){
            dialogueBackgroundZ->show();
            speaker->setText("小Z");
        }

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
    timer->start(0);
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
