#include "battlescene.h"
#include "dialogue.h"
#include "gameboard.h"
#include "mainmenu.h"
#include "mywindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedLayout>

MyWindow::MyWindow(QApplication *_app, QWidget *parent)
    : QWidget{parent}, app(_app)
{
    menu = nullptr;
    dialogue = nullptr;
    battle = nullptr;
    currentBossId = 0;

    layout = new QStackedLayout(this);
//    layout->addWidget(initMainMenu());
    layout->addWidget(initBattle(currentBossId));
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
    dialogueView->setSceneRect(0, 0, 2560, 1440);
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
    return battleView;
}

void MyWindow::startDialogue()
{
    QWidget *w = layout->currentWidget();
    layout->removeWidget(w);
//    delete w;
    layout->addWidget(initDialogue(currentBossId));
}

void MyWindow::startBattle()
{
    QWidget *w = layout->currentWidget();
    layout->removeWidget(w);
//    delete w;
    layout->addWidget(initBattle(currentBossId));
}

void MyWindow::returnMenu()
{
    QWidget *w = layout->currentWidget();
    layout->removeWidget(w);
//    delete w;
    layout->addWidget(initMainMenu());
}

void MyWindow::handleBattleFailed()
{
    startBattle();
}

void MyWindow::handleBattleSucceeded()
{
    if(++currentBossId == 3){
        returnMenu();
    }
    else{
        startDialogue();
    }
}
