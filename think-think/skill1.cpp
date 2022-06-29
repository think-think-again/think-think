#include "skill1.h"
#include "battlescene.h"

Skill1::Skill1(BattleScene *_scene)
    : Skill(_scene, introduction, 1)
{

}

void Skill1::handleMousePress()
{
    if(scene->player->ReturnMp()>=mpCost){
        emit increasePlayerHp(hpIncrement);
        emit increaseMp(-mpCost);
        emit skillPerformed();
        icon->hide();
        layer->hide();
        introductionLabel->hide();
    }
}
