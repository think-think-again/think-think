#include "skill2.h"
#include "battlescene.h"
#include "myglobalvariants.h"

Skill2::Skill2(BattleScene *_scene)
    : Skill(_scene, introduction, 2)
{

}

void Skill2::handleMousePress()
{
    if(BAN_MOUSE_EVENTS) return;
    if(scene->player->ReturnMp()>=mpCost){
        emit increaseBossHp(-attack);
        emit increaseMp(-mpCost);
        emit skillPerformed();
        scene->board->SkillsToGo[1] = 4;
        icon->hide();
        layer->hide();
        introductionLabel->hide();
        introductionLabelProxy->hide();
        layer->hoverDelay->stop();
    }
}
