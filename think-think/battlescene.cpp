#include "battlescene.h"
#include "qscreen.h"

#include <QGraphicsView>
#include <QGuiApplication>

BattleScene::BattleScene(QObject *parent)
    : QGraphicsScene{parent}
{
    // change to screen resolution
    QSize screenSize = QGuiApplication::primaryScreen()->size();
    setSceneRect(0, 0, screenSize.width(), screenSize.height());

    board = new GameBoard;
    QGraphicsScene *boardScene = new QGraphicsScene;
    boardScene->addItem(board);
    QGraphicsView *boardView = new QGraphicsView(boardScene);
    boardView->setRenderHint(QPainter::Antialiasing);
    boardView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setFixedSize(boardScene->sceneRect().size().toSize());
    addWidget(boardView);
}
