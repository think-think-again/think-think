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
#include <QLabel>

class BattleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BattleScene(const QString &name, QObject *parent = nullptr);
    StartButton *returnMenu;
    Player *player;
    GameBoard *board;
private:
    QGraphicsPixmapItem *backgroundMask, *dialogueBackground;
    Boss *boss;
    QProgressBar *BossHp;
    QProgressBar *PlayerHp;
    QProgressBar *PlayerMp;
    Skill *skill[4];
    QLabel *RoundNum;
signals:
    void battleFailed();
    void battleSucceeded();
public slots:
    void increaseMp(int x);
    void increasePlayerHp(int x);
    void increaseBossHp(int x);
    void handleTurnFinished();
};

#endif // BATTLESCENE_H
