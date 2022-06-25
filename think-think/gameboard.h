#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include "boss.h"
#include "player.h"
#include <QGraphicsPixmapItem>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTimer>
#include <random>

class GameBoard : public QObject, public QGraphicsPixmapItem
{

public:
    static constexpr int boardSizeX = 8, boardSizeY = 7;
    static constexpr int swapAnimationDuration = 400;

    explicit GameBoard(Boss* _boss, Player* _player, QGraphicsItem *parent = 0);
    QParallelAnimationGroup *swapGem(int sx, int sy, int dx, int dy);
    bool existMatching();

private:
    Gem *cell[boardSizeX][boardSizeY];
    Boss *boss;
    Player *player;
    std::mt19937 rng;
    std::uniform_int_distribution<int> gemGenerator;
    GemTypes getType(int x, int y);
    GemTypes getBasicType(int x, int y);
    QParallelAnimationGroup *eraseMatchings();
    QPropertyAnimation *moveGem(int gx, int gy, int x, int y, int ax=-1, int ay=-1);

public slots:
    void lazyErase();

};

#endif // GAMEBOARD_H
