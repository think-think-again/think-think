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
    setSceneRect(-screenSize.width()/2, -screenSize.height()/2, screenSize.width(), screenSize.height());

    // set background
    QPixmap bg(":/1080p");
    background = new QGraphicsPixmapItem(bg);
    background->setOffset(-bg.width()/2, -bg.height()/2);
    addItem(background);

    // add start button
    startGame = new StartButton("开始游戏");
    QFont font;
    font.setPixelSize(50);
    startGame->setFont(font);
    startGame->setPos(-startGame->boundingRect().width()/2, 0);
    connect(startGame, &StartButton::clicked,
            parent, &MyWindow::start);
    addItem(startGame);
}
