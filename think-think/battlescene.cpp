#include "battlescene.h"
#include "qscreen.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGuiApplication>

BattleScene::BattleScene(QObject *parent)
    : QGraphicsScene{parent}
{
    // change to screen resolution
    QSize screenSize = QGuiApplication::primaryScreen()->size();
    screenSize = QSize(2560, 1440);
    setSceneRect(0, 0, screenSize.width(), screenSize.height());

    player = new Player;

    boss = new Boss(1);
    addItem(boss);
    boss->setPos(1500,300);
    Boss *_boss = boss;

    board = new GameBoard(_boss);
    QGraphicsScene *boardScene = new QGraphicsScene;
    boardScene->addItem(board);
    QGraphicsView *boardView = new QGraphicsView(boardScene);
    boardView->setRenderHint(QPainter::Antialiasing);
    boardView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setFixedSize(boardScene->sceneRect().size().toSize());
    QGraphicsProxyWidget *boardProxy = addWidget(boardView);
    boardProxy->setPos(300, 300);

}
