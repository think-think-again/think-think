#include "skill2.h"
#include "battlescene.h"

Skill2::Skill2(BattleScene *_scene)
    : Skill(_scene, introduction, 2)
{

}

void Skill2::handleMousePress()
{
    if(scene->player->ReturnMp()>=mpCost){
        emit increaseBossHp(-attack);
        emit increaseMp(-mpCost);
        emit skillPerformed();
        icon->hide();
        layer->hide();
        introductionLabel->hide();
        introductionLabelProxy->hide();
    }
}
