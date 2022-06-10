#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include <QGraphicsPixmapItem>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTimer>
#include <random>

const int boardSizeX = 8, boardSizeY = 7;
const int gemSize = 128;
const int swapAnimationDuration = 200;

class gameBoard : public QObject, public QGraphicsPixmapItem
{
public:
    explicit gameBoard(QGraphicsItem *parent = 0);
    void dragGem(int gx, int gy, int x, int y);

private:
    Gem *cell[boardSizeX][boardSizeY];
    std::mt19937 rng;
    std::uniform_int_distribution<int> gemGenerator;
    bool existMatching();
    GemTypes getType(int x, int y);
    GemTypes getBasicType(int x, int y);
    QParallelAnimationGroup *swapGem(int sx, int sy, int dx, int dy);
    QParallelAnimationGroup *eraseMatchings();
    QPropertyAnimation *moveGem(int gx, int gy, int x, int y, int ax=-1, int ay=-1);

private slots:
    void lazyErase();

};

#endif // GAMEBOARD_H
