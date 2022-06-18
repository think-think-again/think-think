#include "gameboard.h"
#include "mainmenu.h"
#include "mywindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStackedLayout>

myWindow::myWindow(QWidget *parent)
    : QWidget{parent}
{
    QGraphicsScene *scene = new QGraphicsScene;
    gameBoard *board = new gameBoard;
    scene->addItem(board);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(scene->sceneRect().size().toSize());

    mainMenu *menu = new mainMenu(this);
    QGraphicsView *menuView = new QGraphicsView(menu);
    menuView->setRenderHint(QPainter::Antialiasing);
    menuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menuView->setFixedSize(menu->sceneRect().size().toSize());

    layout = new QStackedLayout(this);
    layout->addWidget(view);
    layout->addWidget(menuView);
    layout->setCurrentIndex(1);
}

void myWindow::start()
{
    layout->setCurrentIndex(0);
}
