#include "skill2.h"
#include "battlescene.h"

Skill2::Skill2(BattleScene *_scene)
    : Skill(_scene, introduction)
{

}

void Skill2::handleMousePress()
{
    if(scene->player->ReturnMp()>=mpCost){
        emit increaseBossHp(-attack);
        emit increaseMp(-mpCost);
        emit skillPerformed();
    }
}
