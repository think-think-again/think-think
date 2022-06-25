#include "battlescene.h"
#include "dialogue.h"
#include "gameboard.h"
#include "mainmenu.h"
#include "mywindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedLayout>

MyWindow::MyWindow(QWidget *parent)
    : QWidget{parent}
{
    menu = new MainMenu(this);
    QGraphicsView *menuView = new QGraphicsView(menu);
    menuView->setRenderHint(QPainter::Antialiasing);
    menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setFixedSize(menu->sceneRect().size().toSize());

    dialogue = new Dialogue(this, "ljy");
    QGraphicsView *dialogueView = new QGraphicsView(dialogue);
    dialogueView->setRenderHint(QPainter::Antialiasing);
    dialogueView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    dialogueView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    dialogueView->setFixedSize(dialogue->sceneRect().size().toSize());
    dialogueView->setSceneRect(0, 0, 2560, 1440);
    connect(dialogue, &Dialogue::dialogueEnded,
            this, &MyWindow::startBattle);

    battle = new BattleScene;
    QGraphicsView *battleView = new QGraphicsView(battle);
    battleView->setRenderHint(QPainter::Antialiasing);
    battleView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setFixedSize(battle->sceneRect().size().toSize());

    layout = new QStackedLayout(this);
    layout->addWidget(menuView);
    layout->addWidget(dialogueView);
    layout->addWidget(battleView);
    layout->setCurrentIndex(0);
}

void MyWindow::startDialog()
{
    layout->setCurrentIndex(1);
    dialogue->initialize();
}

void MyWindow::startBattle()
{
    layout->setCurrentIndex(2);
}
