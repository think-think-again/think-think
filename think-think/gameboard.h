#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>
#include <random>

const int boardSizeX = 8, boardSizeY = 7;
const int swapAnimationDuration = 500;

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
    void swapGem(int sx, int sy, int dx, int dy);
    int eraseMatchings();
    int moveGem(int gx, int gy, int x, int y, int ax=-1, int ay=-1);
    void lazyErase();
};

#endif // GAMEBOARD_H
