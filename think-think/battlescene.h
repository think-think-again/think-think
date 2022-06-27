#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "gameboard.h"
#include "boss.h"
#include "player.h"

#include <QGraphicsScene>
#include <QPushButton>
#include <QProgressBar>

class BattleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BattleScene(QObject *parent = nullptr);
private:
    QGraphicsPixmapItem *backgroundMask, *dialogueBackground;
    GameBoard *board;
    Boss *boss;
    Player *player;
    QProgressBar *BossHp;
    QProgressBar *PlayerHp;
    QProgressBar *PlayerMp;
};

#endif // BATTLESCENE_H
