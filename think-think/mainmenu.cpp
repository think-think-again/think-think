#include "mainmenu.h"
#include "mywindow.h"
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QGuiApplication>
#include <QScreen>

MainMenu::MainMenu(QObject *parent)
    : QGraphicsScene{parent}
{
    // change to screen resolution
    QSize screenSize = QGuiApplication::primaryScreen()->size();
    screenSize = QSize(2560, 1440);
    setSceneRect(0, 0, screenSize.width(), screenSize.height());

    // set background
    QPixmap bg(":/resources/main_menu.jpg");
    bg = bg.scaled(screenSize.width(), screenSize.height());
    background = new QGraphicsPixmapItem(bg);
    addItem(background);

    // add start button
    startGame = new StartButton("start");
    startGame->setPos(2560-232, 1440-340);
    addItem(startGame);

    // add exit button
    exitGame = new StartButton("exit");
    exitGame->setPos(2560-240, 1440-200);
    addItem(exitGame);
}
