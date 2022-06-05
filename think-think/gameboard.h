#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>

const int boardSizeX = 8, boardSizeY = 7;
const int swapAnimationDuration = 200;

class gameBoard : public QObject, public QGraphicsPixmapItem
{
public:
    explicit gameBoard(QGraphicsItem *parent = 0);
    void dragGem(int gx, int gy, int x, int y);

private:
    Gem *cell[boardSizeX][boardSizeY];
    bool existMatching();
    GemTypes getType(int x, int y);
    GemTypes getBasicType(int x, int y);
    void swapGem(int sx, int sy, int dx, int dy);
    void eraseMatchings();
    void moveGem(int gx, int gy, int x, int y);
};

#endif // GAMEBOARD_H
