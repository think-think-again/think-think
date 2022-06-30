#include "dialogue.h"
#include "myglobalvariants.h"
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
    if(name=="ljy") bossName = "刘老师";
    if(name=="zqj") bossName = "张老师";
    if(name=="gw") bossName = "郭老师";

    QFile fontFile(":/resources/fonts/FZYanSJW_Zhun.TTF");
    fontFile.open(QIODevice::ReadOnly);
    int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    font.setFamilies(QFontDatabase::applicationFontFamilies(fontId));
    font.setPixelSize(50*SCREEN_SCALE);

    QPixmap _background(":/resources/classroom1.jpg");
    _background = _background.scaled(SCREEN_WIDTH, SCREEN_HEIGHT, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(_background);
    background->setPos(-(_background.width()-SCREEN_WIDTH)/2, -(_background.height()-SCREEN_HEIGHT)/2);
    addItem(background);

    QPixmap _backgroundMask(SCREEN_WIDTH, SCREEN_HEIGHT);
    _backgroundMask.fill(QColor(255, 255, 255, 160));
    backgroundMask = new QGraphicsPixmapItem(_backgroundMask);
    addItem(backgroundMask);

    QPixmap _dialogueBackground(":/resources/character-dialogue/dialogue.png");
    _dialogueBackground = _dialogueBackground.scaled(_dialogueBackground.size()*(SCREEN_SCALE/3));
    dialogueBackground = new QGraphicsPixmapItem(_dialogueBackground);
    dialogueBackground->setPos(MARGIN_HORIZONTAL, MARGIN_VERTICAL*2);
    addItem(dialogueBackground);
    dialogueBackground->hide();

    QPixmap _dialogueBackgroundBoss(":/resources/character-dialogue/" + name + ".png");
    _dialogueBackgroundBoss = _dialogueBackgroundBoss.scaled(_dialogueBackgroundBoss.size()*(SCREEN_SCALE/3));
    dialogueBackgroundBoss = new QGraphicsPixmapItem(_dialogueBackgroundBoss);
    dialogueBackgroundBoss->setPos(MARGIN_HORIZONTAL, MARGIN_VERTICAL*2);
    addItem(dialogueBackgroundBoss);
    dialogueBackgroundBoss->hide();

    QPixmap _dialogueBackgroundZ(":/resources/character-dialogue/z.png");
    _dialogueBackgroundZ = _dialogueBackgroundZ.scaled(_dialogueBackgroundZ.size()*(SCREEN_SCALE/3));
    dialogueBackgroundZ = new QGraphicsPixmapItem(_dialogueBackgroundZ);
    dialogueBackgroundZ->setPos(MARGIN_HORIZONTAL, MARGIN_VERTICAL*2);
    addItem(dialogueBackgroundZ);
    dialogueBackgroundZ->hide();

    QFile json(":/resources/dialogues/" + name + ".json");
    json.open(QIODevice::ReadOnly);
    doc = new QJsonDocument(QJsonDocument::fromJson(json.readAll()));

    prologue = new QLabel();
    /*QGraphicsProxyWidget *prologueProxy = */addWidget(prologue);
    prologue->setWordWrap(true);
    prologue->setAlignment(Qt::AlignTop);
    prologue->setGeometry(400*SCREEN_SCALE+MARGIN_HORIZONTAL, 400*SCREEN_SCALE, (2560-400*2)*SCREEN_SCALE, 500*SCREEN_SCALE);
    prologue->setFont(font);
    prologue->setStyleSheet("QLabel{ background: transparent}");

    dlg = new QLabel();
    QGraphicsProxyWidget *dlgProxy = addWidget(dlg);
    dlgProxy->setZValue(1);
    dlg->setWordWrap(true);
    dlg->setAlignment(Qt::AlignTop);
    dlg->setGeometry(700*SCREEN_SCALE+MARGIN_HORIZONTAL, SCREEN_HEIGHT-372*SCREEN_SCALE, SCREEN_WIDTH-1000*SCREEN_SCALE-MARGIN_HORIZONTAL*2, 372*SCREEN_SCALE);
    dlg->setFont(font);
    dlg->setStyleSheet("QLabel{ background: transparent; color: white}");

    speaker = new QLabel();
    addWidget(speaker);
    speaker->setAlignment(Qt::AlignTop);
    speaker->setGeometry(500*SCREEN_SCALE+MARGIN_HORIZONTAL, SCREEN_HEIGHT-180*SCREEN_SCALE, SCREEN_WIDTH, 180*SCREEN_SCALE);
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
    if(BAN_MOUSE_EVENTS) return;
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
            speaker->setText(bossName);
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
    BAN_MOUSE_EVENTS = true;
    animationStr = str;
    animationLabel = label;
    animationProgress = 0;
    timer->start(30);
}


void Dialogue::updateLabel()
{
    if(animationProgress == animationStr.length()){
        timer->stop();
        BAN_MOUSE_EVENTS = false;
    }
    else{
        QString str = "<p style='line-height: " + QString::number(70*SCREEN_SCALE) + "px'>" + animationStr.left(++animationProgress) + "</p>";
        animationLabel->setText(str);
    }
}
