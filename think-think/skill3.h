#ifndef SKILL3_H
#define SKILL3_H

#include "gameboard.h"
#include "skill.h"
#include <QObject>

class Skill3 : public Skill
{
    Q_OBJECT
public:
    Skill3(GameBoard *_board, Player *_player);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    bool selected;
    GameBoard *board;
    Player *player;
    QProgressBar *MPBar;
public slots:
    void handleSelection(int gx, int gy);
};

#endif // SKILL3_H
