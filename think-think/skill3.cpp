#include "skill3.h"

Skill3::Skill3(BattleScene *_scene, GameBoard *_board, Player *_player)
    : Skill(_scene, introduction)
{
    selected = false;
    board = _board;
    player = _player;
    MPBar = board->PlayerMp;
}

void Skill3::handleMousePress()
{
    if(selected){
        disconnect(board, &GameBoard::select,
                this, &Skill3::handleSelection);
        selected = false;
        QPixmap _icon(":/resources/g.png");
        icon->setPixmap(_icon);
        board->setSkillSelected(false);
    }
    else if (player->ReturnMp() >= 500){
        connect(board, &GameBoard::select,
                this, &Skill3::handleSelection);
        selected = true;
        QPixmap _icon(":/resources/gg.png");
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
    QPixmap _icon(":/resources/g.png");
    icon->setPixmap(_icon);
    board->setSkillSelected(false);
    player->GetMP(-500);
    MPBar->setValue(player->ReturnMp());
    emit skillPerformed();
}
