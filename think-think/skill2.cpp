#include "skill2.h"

Skill2::Skill2(BattleScene *_scene)
    : Skill(_scene, introduction)
{

}

void Skill2::handleMousePress()
{
    qDebug() << "attack boss";
}
