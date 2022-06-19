#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "gameboard.h"

#include <QGraphicsScene>

class BattleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BattleScene(QObject *parent = nullptr);
private:
    GameBoard *board;
};

#endif // BATTLESCENE_H
