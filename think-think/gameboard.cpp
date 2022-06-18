#include "gameboard.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>
#include <random>

gameBoard::gameBoard(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      rng(time(0)),
      gemGenerator(0, 3)
{
    for(int i=0; i<boardSizeX; ++i) for(int j=0; j<boardSizeY; ++j) cell[i][j] = nullptr;
    // TODO: more efficient initialization is needed.
    do{
        for(int i=0; i<boardSizeX; ++i) for(int j=0; j<boardSizeY; ++j){
            if(cell[i][j] != nullptr) delete cell[i][j];
            cell[i][j] = new Gem(GemTypes(1<<gemGenerator(rng)), this, i, j);
            cell[i][j]->setPos(QPointF(i*Gem::gemSize, j*Gem::gemSize));
        }
    } while(existMatching());
}

void gameBoard::lazyErase(){
    QParallelAnimationGroup *group = eraseMatchings();
    if(existMatching()){
        connect(group, &QParallelAnimationGroup::finished,
                this, &gameBoard::lazyErase);
    }
    group->start(QPropertyAnimation::DeleteWhenStopped);
}

GemTypes gameBoard::getType(int x, int y)
{
//    if(x<0 || x>=boardSizeX || y<0 || y>=boardSizeY)
//        qCritical() << "getType out of board bounds";
    return cell[x][y]->getType();
}

GemTypes gameBoard::getBasicType(int x, int y)
{
    if(cell[x][y] == nullptr) return Invalid;
    return getType(x, y) & BasicGemMask;
}

// returns animation duration
QPropertyAnimation *gameBoard::moveGem(int gx, int gy, int x, int y, int ax, int ay)
{
    if(ax == -1 && ay == -1) ax = gx, ay = gy;
    QPropertyAnimation *move = new QPropertyAnimation(cell[gx][gy], "pos");
    move->setStartValue(QPointF(ax*Gem::gemSize, ay*Gem::gemSize));
    move->setEndValue(QPointF(x*Gem::gemSize, y*Gem::gemSize));
    move->setEasingCurve(QEasingCurve::InQuad);
    int duration = sqrt(abs(ax-x)+abs(ay-y))*swapAnimationDuration;
    move->setDuration(duration);
    return move;
}

QParallelAnimationGroup *gameBoard::swapGem(int sx, int sy, int dx, int dy)
{
    QParallelAnimationGroup *g = new QParallelAnimationGroup(this);
    g->addAnimation(moveGem(sx, sy, dx, dy));
    g->addAnimation(moveGem(dx, dy, sx, sy));
    std::swap(cell[sx][sy], cell[dx][dy]);
    cell[sx][sy]->setGPos(sx, sy);
    cell[dx][dy]->setGPos(dx, dy);
    return g;
}

// TODO: the upgrade positon of "xxxx" should be the operate position
QParallelAnimationGroup *gameBoard::eraseMatchings()
{
//    qDebug() << "erase";
    for (int i = 0; i < boardSizeY; ++i){
        for (int j =0; j < boardSizeX; ++j){
            if (i < boardSizeY - 2
                && cell[j][i] != nullptr
                && cell[j][i + 1] != nullptr
                && cell[j][i + 2] != nullptr
                && getType(j, i) != Super
                && getBasicType(j, i) == getBasicType(j, i + 1)
                && getBasicType(j, i + 1) == getBasicType(j, i + 2)){
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
                        cell[j][mem] = new Gem(Super, this, j, mem);
                        cell[j][mem]->setPos(QPointF(j * Gem::gemSize, mem * Gem::gemSize));
                    }
                    else if (mem != -1){
                        cell[j][mem] = new Gem(Upgraded | temp, this, j ,mem);
                        cell[j][mem]->setPos(QPointF(j * Gem::gemSize, mem * Gem::gemSize));
                    }
                }
                else if (cnt == 4) {
                    if (mem == -1) {
                        cell[j][i + 1] = new Gem(Upgraded | temp, this, j, i + 1);
                        cell[j][i + 1]->setPos(QPointF(j * Gem::gemSize, (i + 1) * Gem::gemSize));
                    }
                    else {
                        cell[j][mem] = new Gem(Super, this, j, mem);
                        cell[j][mem]->setPos(QPointF(j * Gem::gemSize, mem * Gem::gemSize));
                    }
                }
                else if (cnt == 5){
                    cell[j][i + 2] = new Gem(Super, this, j, i + 2);
                    cell[j][i + 2]->setPos(QPointF(j * Gem::gemSize, (i + 2) * Gem::gemSize));
                }
            }
            else if (j < boardSizeX - 2
                     && cell[j][i] != nullptr
                     && cell[j + 1][i] != nullptr
                     && cell[j + 2][i] != nullptr
                     && getType(j, i) != Super
                     && getBasicType(j, i) == getBasicType(j + 1, i)
                     && getBasicType(j + 1, i) == getBasicType(j + 2, i)){
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
                        cell[mem][i] = new Gem(temp | Upgraded, this, mem, i);
                        cell[mem][i]->setPos(QPointF(mem * Gem::gemSize, i * Gem::gemSize));
                    }
                }
                else if (cnt == 4){
                    if (mem != -1){
                        cell[mem][i] = new Gem(Super, this, mem, i);
                        cell[mem][i]->setPos(QPointF(mem * Gem::gemSize, i * Gem::gemSize));
                    }
                    else{
                        cell[j + 1][i] = new Gem(temp | Upgraded, this, j + 1, i);
                        cell[j + 1][i]->setPos(QPointF((j + 1) * Gem::gemSize, i * Gem::gemSize));
                    }
                }
                else if (cnt == 5){
                    cell[j + 2][i] = new Gem(Super, this, j + 2, i);
                    cell[j + 2][i]->setPos(QPointF((j + 2)*Gem::gemSize, i * Gem::gemSize));
                }
            }
        }
    }
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    for (int j = 0; j < boardSizeX; ++j){
        for (int i = boardSizeY - 1; i >=0; --i){
            if (cell[j][i] != nullptr) continue;
            int k = i - 1;
            while(cell[j][k] == nullptr){
                k--;
                if (k == -1) break;
            }
            if (k >= 0){
                group->addAnimation(moveGem(j, k, j, i));
                cell[j][i] = cell[j][k];
                cell[j][k] = nullptr;
                cell[j][i]->setGPos(j, i);
            }
        }
        int flag = boardSizeY - 1;
        while(cell[j][flag] != nullptr){
            flag--;
            if (flag == -1) break;
        }
        for (int i = flag; i >=0; --i){
            cell[j][i] = new Gem(GemTypes(1<<gemGenerator(rng)), this, j, i);
            group->addAnimation(moveGem(j, i, j, i, j, i-flag-1));
        }
    }
    return group;
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
