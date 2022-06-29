#include "mainmenu.h"
#include "myglobalvariants.h"
#include "mywindow.h"
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QGuiApplication>
#include <QScreen>

MainMenu::MainMenu(QObject *parent)
    : QGraphicsScene{parent}
{
    // change to screen resolution
    setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // set background
    // 8k resolution (3x)
    QPixmap _background(":/resources/main_menu.jpg");
    _background = _background.scaled(SCREEN_WIDTH, SCREEN_HEIGHT, Qt::KeepAspectRatioByExpanding);
    background = new QGraphicsPixmapItem(_background);
    background->setPos(-(_background.width()-SCREEN_WIDTH)/2, -(_background.height()-SCREEN_HEIGHT)/2);
    addItem(background);

    // add start button
    startGame = new StartButton("start");
    startGame->setPos(SCREEN_WIDTH-232*SCREEN_SCALE, SCREEN_HEIGHT-340*SCREEN_SCALE);
    addItem(startGame);

    // add exit button
    exitGame = new StartButton("exit");
    exitGame->setPos(SCREEN_WIDTH-240*SCREEN_SCALE, SCREEN_HEIGHT-200*SCREEN_SCALE);
    addItem(exitGame);
}
