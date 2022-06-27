#ifndef SKILL2_H
#define SKILL2_H

#include "skill.h"
#include <QObject>

class BattleScene;
class Skill2 : public Skill
{
    static constexpr char introduction[] = "复习：消耗300精力，对老师造成300伤害";
    static const int mpCost = 300, attack = 300;

    Q_OBJECT
public:
    Skill2(BattleScene *_scene);
public slots:
    void handleMousePress();
};

#endif // SKILL2_H
