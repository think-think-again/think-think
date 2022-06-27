#ifndef SKILL4_H
#define SKILL4_H

#include "gameboard.h"
#include "skill.h"
#include <QObject>

class Skill4 : public Skill
{
    Q_OBJECT
public:
    Skill4(GameBoard *_board, Player *_player);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    bool selected;
    GameBoard *board;
    Player *player;
    QProgressBar *MPBar;
public slots:
    void handleSelection(int gx, int gy);
};

#endif // SKILL4_H
