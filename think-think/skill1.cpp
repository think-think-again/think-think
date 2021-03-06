#include "skill1.h"
#include "battlescene.h"
#include "myglobalvariants.h"

Skill1::Skill1(BattleScene *_scene)
    : Skill(_scene, introduction, 1)
{

}

void Skill1::handleMousePress()
{
    if(BAN_MOUSE_EVENTS) return;
    if(scene->player->ReturnMp()>=mpCost){
        emit increasePlayerHp(hpIncrement);
        emit increaseMp(-mpCost);
        emit skillPerformed();
        scene->board->SkillsToGo[0] = 3;
        icon->hide();
        layer->hide();
        introductionLabel->hide();
        layer->hoverDelay->stop();
    }
}
