#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "gameboard.h"
#include "boss.h"
#include "player.h"
#include "skill.h"
#include "startbutton.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QProgressBar>

class BattleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BattleScene(QObject *parent = nullptr);
    StartButton *returnMenu;
    Player *player;
private:
    QGraphicsPixmapItem *backgroundMask, *dialogueBackground;
    GameBoard *board;
    Boss *boss;
    QProgressBar *BossHp;
    QProgressBar *PlayerHp;
    QProgressBar *PlayerMp;
    Skill *skill[4];
public slots:
    void increaseMp(int x);
    void increasePlayerHp(int x);
    void increaseBossHp(int x);
};

#endif // BATTLESCENE_H
