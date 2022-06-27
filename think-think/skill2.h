#ifndef SKILL2_H
#define SKILL2_H

#include "skill.h"
#include <QObject>

class BattleScene;
class Skill2 : public Skill
{
    static constexpr char introduction[] = "复习：对老师造成300点伤害";

    Q_OBJECT
public:
    Skill2(BattleScene *_scene);
public slots:
    void handleMousePress();
};

#endif // SKILL2_H
