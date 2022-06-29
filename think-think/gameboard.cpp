#include "gameboard.h"
#include "myglobalvariants.h"
#include <time.h>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <random>

GameBoard::GameBoard(Boss *_boss,Player* _player, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      rng(time(0)),
      gemGenerator(0, 3),
      m_skillSelected(false)
{
    T = 1;
    boss = _boss;
    player = _player;
    BossSkillTime[0] = 3;
    BossSkillTime[1] = 4;
    BossSkillTime[2] = 5;
    BossSkillTime[3] = 5;
    for(int i=0; i<boardSizeX; ++i) for(int j=0; j<boardSizeY; ++j) cell[i][j] = nullptr;
    // TODO: more efficient initialization is needed.
    do{
        for(int i=0; i<boardSizeX; ++i) for(int j=0; j<boardSizeY; ++j){
            if(cell[i][j] != nullptr) removeGem(i, j);
            cell[i][j] = new Gem(GemTypes(1<<gemGenerator(rng)), this, i, j);
        }
    } while(existMatching());
    BossSkillId = gemGenerator(rng);
    SkillToGo = BossSkillTime[BossSkillId];
    boss->BossSkillId = BossSkillId;
    connect(this, &GameBoard::turnBossSkill, boss, &Boss::Skill);
}

void GameBoard::lazyErase(bool fallFirst){
    BAN_MOUSE_EVENTS = true;
    if(!fallFirst){
        eraseMatchings();
    }
    QParallelAnimationGroup *group = gemsFalling();
    if(existMatching()){
        connect(group, &QParallelAnimationGroup::finished,
                this, [&](){ lazyErase();});
    }
    else{
        connect(group, &QParallelAnimationGroup::finished,
                this, &GameBoard::_turnFinished);
    }
    group->start(QPropertyAnimation::DeleteWhenStopped);
}

void GameBoard::_turnFinished()
{
    BAN_MOUSE_EVENTS = false;
    emit turnFinished();
}

GemTypes GameBoard::getType(int x, int y)
{
//    if(x<0 || x>=boardSizeX || y<0 || y>=boardSizeY)
//        qCritical() << "getType out of board bounds";
    return cell[x][y]->getType();
}

GemTypes GameBoard::getBasicType(int x, int y)
{
    if(cell[x][y] == nullptr) return Invalid;
    return getType(x, y) & BasicGemMask;
}

void GameBoard::upgradeGem(int x, int y)
{
    GemTypes type = cell[x][y]->getType() | Upgraded;
    removeGem(x, y);
    cell[x][y] = new Gem(type, this, x, y);
}

// returns animation duration
QPropertyAnimation *GameBoard::moveGem(int gx, int gy, int x, int y, int ax, int ay)
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

QParallelAnimationGroup *GameBoard::swapGem(int sx, int sy, int dx, int dy)
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
void GameBoard::eraseMatchings()
{
    for (int i = 0; i < boardSizeY; ++i){
        for (int j =0; j < boardSizeX; ++j){
            int BasicNum = 0, UpgradeNum = 0;
            int BasicHit = 0, UpgradeHit = 0;
            GemTypes tempcolor;
            bool flag = false;
            if (i < boardSizeY - 2
                && cell[j][i] != nullptr
                && cell[j][i + 1] != nullptr
                && cell[j][i + 2] != nullptr
                && getType(j, i) != Super
                && getBasicType(j, i) == getBasicType(j, i + 1)
                && getBasicType(j, i + 1) == getBasicType(j, i + 2))
            {
                flag = true;
                GemTypes temp = getBasicType(j, i);
                tempcolor = temp;
                int cnt = 0, mem = -1;
                bool _5 = false;
                for (int k = i; k < boardSizeY && getBasicType(j, k) == temp; ++k){
                    int BranchBasicNum = 0, BranchUpgradeNum = 0;
                    if (cell[j][k]->getType() & Upgraded) UpgradeNum++;
                    else BasicNum++;
                    cnt++;
                    removeGem(j, k);
                    int sumcol = 0;
                    for (int l = j - 1; l >= 0 && getBasicType(l, k) == temp; --l) {
                        sumcol++;
                        if (cell[l][k]->getType() & Upgraded) BranchUpgradeNum++;
                        else BranchBasicNum++;
                    }
                    for (int l = j + 1; l < boardSizeX && getBasicType(l, k) == temp; ++l){
                        sumcol++;
                        if (cell[l][k]->getType() & Upgraded) BranchUpgradeNum++;
                        else BranchBasicNum++;
                    }
                    if (sumcol >= 2){
                        mem = k;
                        BasicNum += BranchBasicNum;
                        UpgradeNum += BranchUpgradeNum;
                        if (sumcol == 4) _5 = true;
                        for (int l = j - 1; l >= 0 && getBasicType(l, k) == temp; --l){
                            removeGem(l, k);
                        }
                        for (int l = j + 1; l < boardSizeX && getBasicType(l, k) == temp; ++l){
                            removeGem(l, k);
                        }
                    }
                }
                if (cnt == 3) {
                    if (_5)
                    {
                        cell[j][mem] = new Gem(Super, this, j, mem);
                        BasicHit = 4;
                    }
                    else if (mem != -1) {
                        cell[j][mem] = new Gem(Upgraded | temp, this, j, mem);
                        BasicHit = 3;
                    }
                    else {
                        BasicHit = 1;
                    }
                }
                else if (cnt == 4) {
                    if (mem == -1) {
                        cell[j][i + 1] = new Gem(Upgraded | temp, this, j, i + 1);
                        BasicHit = 2;
                    }
                    else {
                        cell[j][mem] = new Gem(Upgraded | temp, this, j, mem);
                        BasicHit = 3;
                    }
                }
                else if (cnt == 5){
                    cell[j][i + 2] = new Gem(Super, this, j, i + 2);
                    BasicHit = 4;
                }
            }
            else if (j < boardSizeX - 2
                     && cell[j][i] != nullptr
                     && cell[j + 1][i] != nullptr
                     && cell[j + 2][i] != nullptr
                     && getType(j, i) != Super
                     && getBasicType(j, i) == getBasicType(j + 1, i)
                     && getBasicType(j + 1, i) == getBasicType(j + 2, i))
            {
                flag = true;
                GemTypes temp = getBasicType(j, i);
                tempcolor = temp;
                int cnt = 0, mem = -1;
                bool _4 = false;
                for (int l = j; l < boardSizeX && getBasicType(l, i) == temp; ++l){
                    int BranchUpgradeNum = 0;
                    if (cell[l][i]->getType() & Upgraded) UpgradeNum++;
                    cnt++;
                    removeGem(l, i);
                    int sumrow = 0;
                    for (int k = i - 1; k >= 0 && getBasicType(l, k) == temp; --k){
                        sumrow++;
                        if (cell[l][k]->getType() & Upgraded) BranchUpgradeNum++;
                    }
                    for (int k = i + 1; k < boardSizeY && getBasicType(l, k) == temp; ++k){
                        sumrow++;
                        if (cell[l][k]->getType() & Upgraded) BranchUpgradeNum++;
                    }
                    if (sumrow >= 2){
                        UpgradeNum += BranchUpgradeNum;
                        mem = l;
                        if (sumrow == 3) _4 = true;
                        for (int k = i - 1; k >= 0 && getBasicType(l, k) == temp; --k){
                            removeGem(l, k);
                        }
                        for (int k = i + 1; k < boardSizeY && getBasicType(l, k) == temp; ++k){
                            removeGem(l, k);
                        }
                    }
                }
                if (cnt == 3){
                    if (!_4 && mem != -1){
                        cell[mem][i] = new Gem(temp | Upgraded, this, mem, i);
                        BasicHit = 3;
                    }
                    else BasicHit = 1;
                }
                else if (cnt == 4){
                    if (mem != -1){
                        cell[mem][i] = new Gem(Upgraded | temp, this, mem, i);
                        BasicHit = 3;
                    }
                    else{
                        cell[j + 1][i] = new Gem(temp | Upgraded, this, j + 1, i);
                        BasicHit = 2;
                    }
                }
                else if (cnt == 5){
                    cell[j + 2][i] = new Gem(Super, this, j + 2, i);
                    BasicHit = 4;
                }
            }
            if (flag)
            {
                UpgradeHit = UpgradeNum * BasicHit;
                if (tempcolor == Blue) {
                    boss->hurt((player->Attack * player->debuff - boss->getPD()) * BasicHit + (int)(player->Attack * player->debuff - boss->getPD()) * player->UpgradeRateBlue * UpgradeHit);
                    BossHp->setValue(boss->GetHp());
                }
                else if (tempcolor == Red) {
                    boss->hurt((player->Attack * player->debuff - boss->getMD()) * BasicHit + (int)(player->Attack * player->debuff - boss->getMD())* player->UpgradeRateRed * UpgradeHit);
                    BossHp->setValue(boss->GetHp());
                }
                else if (tempcolor == Green) {
                    player->GetHP(player->getHP * player->debuff * BasicHit + (int)player->getHP * player->debuff * player->UpgardeRateGreen * UpgradeHit);
                    PlayerHp->setValue(player->ReturnHp());
                }
                else if (tempcolor == Orange) {
                    player->GetMP(player->getMP * player->debuff * BasicHit + (int)player->getMP * player->debuff * player->UpgradeRateOrange * UpgradeHit);
                    PlayerMp->setValue(player->ReturnMp());
                }
            }
        }
    }
}

QParallelAnimationGroup *GameBoard::gemsFalling(){
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

bool GameBoard::existMatching()
{
    for (int i = 0; i < boardSizeX; ++i) {
        for (int j = 0; j < boardSizeY; ++j) {
            if (i < boardSizeX-2 &&
                getBasicType(i, j) == getBasicType(i + 1, j) &&
                getBasicType(i + 1, j) == getBasicType(i + 2, j) && getType(i, j) != Super) return true;
            if (j < boardSizeY-2 &&
                getBasicType(i, j) == getBasicType(i, j + 1) &&
                getBasicType(i, j + 1) == getBasicType(i, j + 2) && getType(i, j) != Super) return true;
        }
    }
    return false;
}

bool GameBoard::skillSelected()
{
    return m_skillSelected;
}

void GameBoard::setSkillSelected(bool _skillSelected)
{
    m_skillSelected = _skillSelected;
}

void GameBoard::emitSelection(int gx, int gy)
{
    emit select(gx, gy);
}

void GameBoard::removeGem(int gx, int gy)
{
    cell[gx][gy]->deleteLater();
    cell[gx][gy] = nullptr;
}
int GameBoard::RandomNum() {
    return gemGenerator(rng);
}
