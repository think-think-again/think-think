#ifndef SKILL3_H
#define SKILL3_H

#include "gameboard.h"
#include "skill.h"
#include <QObject>

class BattleScene;
class Skill3 : public Skill
{
    static constexpr char introduction[] = "intro";

    Q_OBJECT
public:
    Skill3(BattleScene *_scene, GameBoard *_board, Player *_player);
private:
    bool selected;
    GameBoard *board;
    Player *player;
    QProgressBar *MPBar;
public slots:
    void handleSelection(int gx, int gy);
    void handleMousePress();
};

#endif // SKILL3_H
