#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>

const int boardSizeX = 8, boardSizeY = 7;

class gameBoard : public QGraphicsPixmapItem
{
public:
    explicit gameBoard(QGraphicsItem *parent = 0);
    void gemMove(int gx, int gy, int x, int y);

private:
    Gem *cell[boardSizeX][boardSizeY];
    bool existMatching();
    GemTypes getType(int x, int y);
    GemTypes getBasicType(int x, int y);
};

#endif // GAMEBOARD_H
