#include "gameboard.h"

#include <QPropertyAnimation>
#include <QTimer>
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

void gameBoard::dragGem(int gx, int gy, int x, int y)
{
//    qDebug() << gx << gy << x << y;
    x+=gx, y+=gy;
    if(0<=x && x<boardSizeX && 0<=y && y<boardSizeY){
        swapGem(gx, gy, x, y);
        QTimer::singleShot(swapAnimationDuration, [&, gx, gy, x, y](){
            if(!existMatching()){
                swapGem(gx, gy, x, y);
            }
            else{
                eraseMatchings();
            }
        });
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

void gameBoard::moveGem(int gx, int gy, int x, int y)
{
    QPropertyAnimation *move = new QPropertyAnimation(cell[gx][gy], "pos");
    move->setStartValue(QPointF(gx*64, gy*64));
    move->setEndValue(QPointF(x*64, y*64));
    move->setDuration(swapAnimationDuration);
    move->start(QPropertyAnimation::DeleteWhenStopped);
}

void gameBoard::swapGem(int gx, int gy, int x, int y)
{
    moveGem(gx, gy, x, y);
    moveGem(x, y, gx, gy);
    std::swap(cell[gx][gy], cell[x][y]);
    cell[gx][gy]->setGPos(gx, gy);
    cell[x][y]->setGPos(x, y);
}

void gameBoard::eraseMatchings()
{
    qDebug() << "erase";
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
