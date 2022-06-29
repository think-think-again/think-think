#include "skill4.h"

Skill4::Skill4(BattleScene *_scene, GameBoard *_board, Player *_player)
    : Skill(_scene, introduction, 4)
{
    selected = false;
    board = _board;
    player = _player;
    MPBar = board->PlayerMp;
}

void Skill4::handleMousePress()
{
    if(selected){
        disconnect(board, &GameBoard::select,
                this, &Skill4::handleSelection);
        selected = false;
        QPixmap _icon(":/resources/skills/skill4.png");
        icon->setPixmap(_icon);
        board->setSkillSelected(false);
    }
    else if (player->ReturnMp() >= 800){
        connect(board, &GameBoard::select,
                this, &Skill4::handleSelection);
        selected = true;
        QPixmap _icon(":/resources/skills/skill4-s.png");
        icon->setPixmap(_icon);
        board->setSkillSelected(true);
    }
}

void Skill4::handleSelection(int gx, int gy)
{
    if(board->getType(gx, gy) != Super && !(board->getType(gx, gy) & Upgraded)){
        board->upgradeGem(gx, gy);
        disconnect(board, &GameBoard::select,
                this, &Skill4::handleSelection);
        selected = false;
        QPixmap _icon(":/resources/skills/skill4.png");
        icon->setPixmap(_icon);
        board->setSkillSelected(false);
        player->GetMP(-800);
        MPBar->setValue(player->ReturnMp());
        emit skillPerformed();
        icon->hide();
        layer->hide();
        introductionLabel->hide();
        introductionLabelProxy->hide();
    }
}
