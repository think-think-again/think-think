#include "skill3.h"
#include "myglobalvariants.h"

Skill3::Skill3(BattleScene *_scene, GameBoard *_board, Player *_player)
    : Skill(_scene, introduction, 3)
{
    selected = false;
    board = _board;
    player = _player;
    MPBar = board->PlayerMp;
}

void Skill3::handleMousePress()
{
    if(BAN_MOUSE_EVENTS) return;
    if(selected){
        disconnect(board, &GameBoard::select,
                this, &Skill3::handleSelection);
        selected = false;
        QPixmap _icon(":/resources/skills/skill3.png");
        icon->setPixmap(_icon);
        board->setSkillSelected(false);
    }
    else if (player->ReturnMp() >= 500){
        connect(board, &GameBoard::select,
                this, &Skill3::handleSelection);
        selected = true;
        QPixmap _icon(":/resources/skills/skill3-s.png");
        icon->setPixmap(_icon);
        board->setSkillSelected(true);
    }
}

void Skill3::handleSelection(int gx, int gy)
{
    board->removeGem(gx, gy);
    board->lazyErase(true);
    disconnect(board, &GameBoard::select,
            this, &Skill3::handleSelection);
    selected = false;
    QPixmap _icon(":/resources/skills/skill3.png");
    icon->setPixmap(_icon);
    board->setSkillSelected(false);
    player->GetMP(-500);
    MPBar->setValue(player->ReturnMp());
    emit skillPerformed();
    icon->hide();
    layer->hide();
    introductionLabel->hide();
    layer->hoverDelay->stop();
    board->SkillsToGo[2] = 6;
}
