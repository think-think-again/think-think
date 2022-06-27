#include "skill1.h"

Skill1::Skill1(BattleScene *_scene)
    : Skill(_scene, introduction)
{

}

void Skill1::handleMousePress()
{
    qDebug() << "hp++";
}
