#include "skill4.h"

Skill4::Skill4(GameBoard *_board, Player *_player)
{
    selected = false;
    board = _board;
    player = _player;
    MPBar = board->PlayerMp;
}

void Skill4::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(selected){
        disconnect(board, &GameBoard::select,
                this, &Skill4::handleSelection);
        selected = false;
        QPixmap icon(":/resources/g.png");
        setPixmap(icon);
        board->setSkillSelected(false);
    }
    else if (player->ReturnMp() >= 800){
        connect(board, &GameBoard::select,
                this, &Skill4::handleSelection);
        selected = true;
        QPixmap icon(":/resources/gg.png");
        setPixmap(icon);
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
        QPixmap icon(":/resources/g.png");
        setPixmap(icon);
        board->setSkillSelected(false);
        player->GetMP(-800);
        MPBar->setValue(player->ReturnMp());
    }
}
