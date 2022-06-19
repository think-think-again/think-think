#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "gameboard.h"
#include "boss.h"

#include <QGraphicsScene>

class BattleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BattleScene(QObject *parent = nullptr);
private:
    GameBoard *board;
    Boss *boss;
};

#endif // BATTLESCENE_H
