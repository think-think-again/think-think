#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gem.h"
#include "boss.h"
#include "player.h"

#include <QGraphicsPixmapItem>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <random>
#include <QProgressBar>
#include <QLabel>

class GameBoard : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    static constexpr int boardSizeX = 8, boardSizeY = 7;
    static constexpr int swapAnimationDuration = 200;

    explicit GameBoard(Boss* _boss, Player* _player, QGraphicsItem *parent = 0);
    GemTypes getType(int x, int y);
    GemTypes getBasicType(int x, int y);
    void upgradeGem(int x, int y);
    QParallelAnimationGroup *swapGem(int sx, int sy, int dx, int dy);
    bool existMatching();
    bool skillSelected();
    void setSkillSelected(bool _skillSelected);
    void emitSelection(int gx, int gy);
    void removeGem(int gx, int gy);
    QParallelAnimationGroup *gemsFalling();
    int RandomNum();
    int T;
    int SkillToGo;
    int BossSkillId;
    int BossSkillTime[4];
    Boss *boss;
    QProgressBar *BossHp;
    QProgressBar *PlayerHp;
    QProgressBar *PlayerMp;
    QLabel *RoundNum;
    QLabel *BossSkillIntroduction;
    Player *player;
private:
    Gem *cell[boardSizeX][boardSizeY];

    std::mt19937 rng;
    std::uniform_int_distribution<int> gemGenerator;
    void eraseMatchings();
    QPropertyAnimation *moveGem(int gx, int gy, int x, int y, int ax=-1, int ay=-1);
    bool m_skillSelected;
    const int UpperRound = 40;

signals:
    void select(int, int);
    void turnFinished();
    void turnBossSkill();

public slots:
    void lazyErase(bool fallFirst = false);
    void _turnFinished();

};

#endif // GAMEBOARD_H
