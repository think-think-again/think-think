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
                do{
                    eraseMatchings();
                }while(existMatching());
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
    bool flag = false;
    for (int i = 0; i < boardSizeY; ++i){
        if (flag) break;
        for (int j =0; j < boardSizeX; ++j){
            if (i < boardSizeY - 2 && getBasicType(j, i) == getBasicType(j, i + 1) && getBasicType(j, i + 1) == getBasicType(j, i + 2)){
                GemTypes temp = getBasicType(j, i);
                int cnt = 0, mem = -1;
                bool _4 = false;
                for (int k = i; k < boardSizeY && getBasicType(j, k) == temp; ++k){
                    cnt++;
                    delete cell[j][k];
                    cell[j][k] = nullptr;
                    int sumcol = 0;
                    for (int l = j - 1; l >= 0 && getBasicType(l, k) == temp; --l) sumcol++;
                    for (int l = j + 1; l < boardSizeX && getBasicType(l, k) == temp; ++l) sumcol++;
                    if (sumcol >= 2){
                        mem = k;
                        if (sumcol == 3) _4 = true;
                        for (int l = j - 1; l >= 0 && getBasicType(l, k) == temp; --l){
                            delete cell[l][k];
                            cell[l][k] = nullptr;
                        }
                        for (int l = j + 1; l < boardSizeX && getBasicType(l, k) == temp; ++l){
                            delete cell[l][k];
                            cell[l][k] = nullptr;
                        }
                    }
                }
                if (cnt == 3) {
                    if (_4) {
                        cell[j][mem] = new Gem(GemTypes(Super), this, j, mem);
                        cell[j][mem]->setPos(QPointF(j * 64, mem * 64));
                    }
                }
                else if (cnt == 4) {
                    if (mem == -1) {
                        cell[j][i + 1] = new Gem(GemTypes(Upgraded | temp), this, j, i + 1);
                        cell[j][i + 1]->setPos(QPointF(j * 64, (i + 1) * 64));
                    }
                    else {
                        cell[j][mem] = new Gem(GemTypes(Super), this, j, mem);
                        cell[j][mem]->setPos(QPointF(j * 64, mem * 64));
                    }
                }
                else if (cnt == 5){
                    cell[j][i + 2] = new Gem(GemTypes(Super), this, j, i + 2);
                    cell[j][i + 2]->setPos(QPointF(j * 64, (i + 2) * 64));
                }
                flag = true;
                break;
            }
            else if (j < boardSizeX - 2 && getBasicType(j, i) == getBasicType(j + 1, i) && getBasicType(j + 1, i) == getBasicType(j + 2, i)){
                GemTypes temp = getBasicType(j, i);
                int cnt = 0, mem = -1;
                bool _4 = false;
                for (int l = j; l < boardSizeX && getBasicType(l, i) == temp; ++l){
                    cnt++;
                    delete cell[l][i];
                    cell[l][i] = nullptr;
                    int sumrow = 0;
                    for (int k = i - 1; k >= 0 && getBasicType(l, k) == temp; --k) sumrow++;
                    for (int k = i + 1; k < boardSizeY && getBasicType(l, k) == temp; ++k) sumrow++;
                    if (sumrow >= 2){
                        mem = l;
                        if (sumrow == 3) _4 = true;
                        for (int k = i - 1; k >= 0 && getBasicType(l, k) == temp; --k){
                            delete cell[l][k];
                            cell[l][k] = nullptr;
                        }
                        for (int k = i + 1; k < boardSizeY && getBasicType(l, k) == temp; ++k){
                            delete cell[l][k];
                            cell[l][k] = nullptr;
                        }
                    }
                }
                if (cnt == 3){
                    if (!_4 && mem != -1){
                        cell[mem][i] = new Gem(GemTypes(temp | Upgraded), this, mem, i);
                        cell[mem][i]->setPos(QPointF(mem * 64, i * 64));
                    }
                }
                else if (cnt == 4){
                    if (mem != -1){
                        cell[mem][i] = new Gem(GemTypes(Super), this, mem, i);
                        cell[mem][i]->setPos(QPointF(mem * 64, i * 64));
                    }
                    else{
                        cell[j + 1][i] = new Gem(GemTypes(temp | Upgraded), this, j + 1, i);
                        cell[j + 1][i]->setPos(QPointF((j + 1) * 64, i * 64));
                    }
                }
                else if (cnt == 5){
                    cell[j + 2][i] = new Gem(GemTypes(Super), this, j + 2, i);
                    cell[j + 2][i]->setPos(QPointF((j + 2)*64, i * 64));
                }
                flag = true;
                break;
            }
        }
    }
    for (int j = 0; j < boardSizeX; ++j){
        for (int i = boardSizeY - 1; i >=0; --i){
            if (cell[j][i] != nullptr) continue;
            int k = i - 1;
            while(cell[j][k] == nullptr){
                k--;
                if (k == -1) break;
            }
            if (k >= 0){
                cell[j][i] = new Gem(cell[j][k]->getType(), this, j, i);
                cell[j][i]->setPos(QPointF(j * 64, i * 64));
                delete cell[j][k];
                cell[j][k] = nullptr;
            }
        }
        int flag = boardSizeY - 1;
        while(cell[j][flag] != nullptr){
            flag--;
            if (flag == -1) break;
        }
        std::mt19937 gen(time(0));
        std::uniform_int_distribution<int> col(0, 3);
        for (int i = flag; i >=0; --i){
            cell[j][i] = new Gem(GemTypes(1<<col(gen)), this, j, i);
            cell[j][i]->setPos(QPointF(j*64, i*64));
        }
    }
    return;
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
