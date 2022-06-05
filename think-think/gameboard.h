#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>

const int boardSize = 9;

class gameBoard : public QGraphicsPixmapItem
{
public:
    explicit gameBoard(QGraphicsItem *parent = 0);
    void gemMove(int gx, int gy, int x, int y);

private:
    Gem *cell[boardSize][boardSize];
};

#endif // GAMEBOARD_H
