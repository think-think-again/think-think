#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include <QGraphicsPixmapItem>

const int boardSize = 9;

class gameBoard : public QGraphicsPixmapItem
{
public:
    explicit gameBoard(QGraphicsItem *parent = 0);

private:
    Gem *cell[boardSize][boardSize];
};

#endif // GAMEBOARD_H
