#include "battlescene.h"
#include "gameboard.h"
#include "mainmenu.h"
#include "mywindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedLayout>

MyWindow::MyWindow(QWidget *parent)
    : QWidget{parent}
{
    BattleScene *battle = new BattleScene;
    QGraphicsView *battleView = new QGraphicsView(battle);
    battleView->setRenderHint(QPainter::Antialiasing);
    battleView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    battleView->setFixedSize(battle->sceneRect().size().toSize());

    MainMenu *menu = new MainMenu(this);
    QGraphicsView *menuView = new QGraphicsView(menu);
    menuView->setRenderHint(QPainter::Antialiasing);
    menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setFixedSize(menu->sceneRect().size().toSize());

    layout = new QStackedLayout(this);
    layout->addWidget(battleView);
    layout->addWidget(menuView);
    layout->setCurrentIndex(1);
}

void MyWindow::start()
{
    layout->setCurrentIndex(0);
}
