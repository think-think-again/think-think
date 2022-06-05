#include "gameboard.h"

#include <QPropertyAnimation>
#include <random>

gameBoard::gameBoard(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> col(0, 3);
    for(int i=0; i<boardSizeX; ++i) for(int j=0; j<boardSizeY; ++j) cell[i][j] = nullptr;
    // TODO: more efficient initialization is needed.
    do{
        for(int i=0; i<boardSizeX; ++i) for(int j=0; j<boardSizeY; ++j){
            if(cell[i][j] != nullptr) delete cell[i][j];
            cell[i][j] = new Gem(GemTypes(1<<col(gen)), this, i, j);
            cell[i][j]->setPos(QPointF(i*64, j*64));
        }
    } while(existMatching());
}

void gameBoard::gemMove(int gx, int gy, int x, int y)
{
//    qDebug() << gx << gy << x << y;
    x+=gx, y+=gy;
    if(0<=x && x<boardSizeX && 0<=y && y<boardSizeY){
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

GemTypes gameBoard::getType(int x, int y)
{
    if(x<0 || x>=boardSizeX || y<0 || y>=boardSizeY)
        qCritical() << "getType out of board bounds";
    return cell[x][y]->getType();
}

GemTypes gameBoard::getBasicType(int x, int y)
{
    return getType(x, y) & BasicGemMask;
}

bool gameBoard::existMatching()
{
    for (int i = 0; i < boardSizeX; ++i) {
        for (int j = 0; j < boardSizeY; ++j) {
            if (i < boardSizeX-2 &&
                getBasicType(i, j) == getBasicType(i + 1, j) &&
                getBasicType(i + 1, j) == getBasicType(i + 2, j)) return true;
            if (j < boardSizeY-2 &&
                getBasicType(i, j) == getBasicType(i, j + 1) &&
                getBasicType(i, j + 1) == getBasicType(i, j + 2)) return true;
        }
    }
    return false;
}
