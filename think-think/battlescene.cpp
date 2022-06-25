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

    QPixmap _background(":/resources/classroom1.jpg");
    _background = _background.scaled(2560, 1440, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(_background);
    background->setPos(-(_background.width()-2560)/2, -(_background.height()-1440)/2);
    addItem(background);

    QPixmap _backgroundMask(2560, 1440);
    _backgroundMask.fill(QColor(255, 255, 255, 90));
    backgroundMask = new QGraphicsPixmapItem(_backgroundMask);
    addItem(backgroundMask);

    player = new Player;
    Player* _player = player;

    boss = new Boss(1);
    addItem(boss);
    Boss *_boss = boss;

    board = new GameBoard(_boss, _player);
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
