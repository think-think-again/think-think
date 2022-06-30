#ifndef SKILL1_H
#define SKILL1_H

#include "skill.h"
#include <QObject>

class BattleScene;
class Skill1 : public Skill
{
    static constexpr char introduction[] = "热带风味：消耗100精神力，恢复100生命值";
    static const int mpCost = 100, hpIncrement = 100;

    Q_OBJECT
public:
    Skill1(BattleScene *_scene);
public slots:
    void handleMousePress();
};

#endif // SKILL1_H
