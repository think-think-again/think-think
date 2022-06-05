#include "gameboard.h"

#include <random>

gameBoard::gameBoard(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> col(0, gemTypeNum-1);
    for(int i=0; i<boardSize; ++i)
        for(int j=0; j<boardSize; ++j){
            cell[i][j] = new Gem(gemType(col(gen)), this);
            cell[i][j]->setPos(i*64, j*64);
        }
}
