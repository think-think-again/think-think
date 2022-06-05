#include "gameboard.h"

#include <QPropertyAnimation>
#include <random>

gameBoard::gameBoard(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> col(0, gemTypeNum-1);
    for(int i=0; i<boardSize; ++i)
        for(int j=0; j<boardSize; ++j){
            cell[i][j] = new Gem(gemType(col(gen)), this, i, j);
            cell[i][j]->setPos(QPointF(i*64, j*64));
        }
}

void gameBoard::gemMove(int gx, int gy, int x, int y)
{
//    qDebug() << gx << gy << x << y;
    x+=gx, y+=gy;
    if(0<=x && x<boardSize && 0<=y && y<boardSize){
        QPropertyAnimation *move1 = new QPropertyAnimation(cell[gx][gy], "pos");
        move1->setStartValue(QPointF(gx*64, gy*64));
        move1->setEndValue(QPointF(x*64, y*64));
        move1->setDuration(300);
        move1->start(QPropertyAnimation::DeleteWhenStopped);

        QPropertyAnimation *move2 = new QPropertyAnimation(cell[x][y], "pos");
        move2->setStartValue(QPointF(x*64, y*64));
        move2->setEndValue(QPointF(gx*64, gy*64));
        move2->setDuration(300);
        move2->start(QPropertyAnimation::DeleteWhenStopped);

        std::swap(cell[gx][gy], cell[x][y]);
        cell[gx][gy]->setGPos(gx, gy);
        cell[x][y]->setGPos(x, y);
    }
}
