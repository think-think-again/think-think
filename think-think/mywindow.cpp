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
    MainMenu *menu = new MainMenu(this);
    QGraphicsView *menuView = new QGraphicsView(menu);
    menuView->setRenderHint(QPainter::Antialiasing);
    menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setFixedSize(menu->sceneRect().size().toSize());

    Dialogue *dialog = new Dialogue(this);

    BattleScene *battle = new BattleScene;
    QGraphicsView *battleView = new QGraphicsView(battle);
    battleView->setRenderHint(QPainter::Antialiasing);
    battleView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setFixedSize(battle->sceneRect().size().toSize());

    layout = new QStackedLayout(this);
    layout->addWidget(menuView);
    layout->addWidget(dialog);
    layout->addWidget(battleView);
    layout->setCurrentIndex(0);
}

void MyWindow::startDialog()
{
    layout->setCurrentIndex(1);
}

void MyWindow::startBattle()
{
    layout->setCurrentIndex(2);
}
