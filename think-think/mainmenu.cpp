#include "mainmenu.h"
#include "mywindow.h"
#include <QFont>
#include <QGraphicsPixmapItem>
#include <QGuiApplication>
#include <QScreen>

MainMenu::MainMenu(MyWindow *parent)
    : QGraphicsScene{(QObject *)parent},
      window(parent)
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
    startGame = new StartButton();
    startGame->setPos(2560-600/3, 1440-350/3);
    connect(startGame, &StartButton::clicked,
            parent, &MyWindow::startDialog);
    addItem(startGame);

    // add exit button
    exitGame = new ExitButton();
    exitGame->setPos(2560-600/3, 1440-100/3);
    connect(exitGame, &ExitButton::clicked,
            parent, &MyWindow::startDialog);
    addItem(exitGame);
}
