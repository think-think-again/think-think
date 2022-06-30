#include "battlescene.h"
#include "dialogue.h"
#include "gameboard.h"
#include "mainmenu.h"
#include "myglobalvariants.h"
#include "mywindow.h"

#include <QAudioOutput>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QStackedLayout>

MyWindow::MyWindow(QApplication *_app, QWidget *parent)
    : QWidget{parent}, app(_app)
{
    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput;
    audioOutput->setVolume(100);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/resources/Lovely Piano Song.mp3"));
    musicPlayer->play();
    connect(musicPlayer, &QMediaPlayer::playbackStateChanged,
            this, &MyWindow::playMusicAgain);

    menu = nullptr;
    dialogue = nullptr;
    battle = nullptr;
    currentBossId = 0;
    battleOpacity = new QGraphicsOpacityEffect;

    layout = new QStackedLayout(this);
    layout->addWidget(initMainMenu());
//    layout->addWidget(initBattle(currentBossId));
}

QGraphicsView *MyWindow::initMainMenu()
{
    menu = new MainMenu(this);
    connect(menu->startGame, &StartButton::clicked,
            this, &MyWindow::startDialogue);
    connect(menu->exitGame, &StartButton::clicked,
            app, &QApplication::quit);
    QGraphicsView *menuView = new QGraphicsView(menu);
    menuView->setRenderHint(QPainter::Antialiasing);
    menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setFixedSize(menu->sceneRect().size().toSize());
    return menuView;
}

QGraphicsView *MyWindow::initDialogue(int bossId)
{
    dialogue = new Dialogue(this, bossNames[bossId]);
    dialogue->initialize();
    connect(dialogue, &Dialogue::dialogueEnded,
            this, &MyWindow::startBattle);
    QGraphicsView *dialogueView = new QGraphicsView(dialogue);
    dialogueView->setRenderHint(QPainter::Antialiasing);
    dialogueView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dialogueView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dialogueView->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    return dialogueView;
}

QGraphicsView *MyWindow::initBattle(int bossId)
{
    battle = new BattleScene(bossNames[bossId]);
    connect(battle->returnMenu, &StartButton::clicked,
            this, &MyWindow::returnMenu);
    connect(battle, &BattleScene::battleFailed,
            this, &MyWindow::handleBattleFailed);
    connect(battle, &BattleScene::battleSucceeded,
            this, &MyWindow::handleBattleSucceeded);
    QGraphicsView *battleView = new QGraphicsView(battle);
    battleView->setRenderHint(QPainter::Antialiasing);
    battleView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setFixedSize(battle->sceneRect().size().toSize());
    battle->boss->setGraphicsEffect(battleOpacity);
    battleOpacity->setOpacity(1);
    return battleView;
}

void MyWindow::startDialogue()
{

    BAN_MOUSE_EVENTS = false;
    QWidget *w = layout->currentWidget();
    layout->removeWidget(w);
    w->deleteLater();
    layout->addWidget(initDialogue(currentBossId));
}

void MyWindow::startBattle()
{
    QWidget *w = layout->currentWidget();
    layout->removeWidget(w);
    w->deleteLater();
    layout->addWidget(initBattle(currentBossId));
}

void MyWindow::returnMenu()
{
    BAN_MOUSE_EVENTS = false;
    QWidget *w = layout->currentWidget();
    layout->removeWidget(w);
    w->deleteLater();
    layout->addWidget(initMainMenu());
}

void MyWindow::handleBattleFailed()
{
    startBattle();
}

void MyWindow::handleBattleSucceeded()
{
    BAN_MOUSE_EVENTS = true;
    battle->boss->floating->stop();
    QPropertyAnimation *fade = new QPropertyAnimation(battleOpacity, "opacity");
    fade->setStartValue(1);
    fade->setEndValue(0);
    fade->setDuration(2000);
    if(++currentBossId == 3){
        connect(fade, &QPropertyAnimation::finished,
                this, &MyWindow::returnMenu);
    }
    else{
        connect(fade, &QPropertyAnimation::finished,
                this, &MyWindow::startDialogue);
    }
    fade->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyWindow::playMusicAgain(QMediaPlayer::PlaybackState newState)
{
    musicPlayer->deleteLater();
    musicPlayer = new QMediaPlayer(this);
    musicPlayer->setAudioOutput(audioOutput);
    musicPlayer->setSource(QUrl("qrc:/resources/Lovely Piano Song.mp3"));
    musicPlayer->play();
    connect(musicPlayer, &QMediaPlayer::playbackStateChanged,
            this, &MyWindow::playMusicAgain);
}
