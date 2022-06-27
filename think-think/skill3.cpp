#include "skill3.h"

Skill3::Skill3(GameBoard *_board, Player *_player)
{
    selected = false;
    board = _board;
    player = _player;
    MPBar = board->PlayerMp;
}

void Skill3::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(selected){
        disconnect(board, &GameBoard::select,
                this, &Skill3::handleSelection);
        selected = false;
        QPixmap icon(":/resources/g.png");
        setPixmap(icon);
        board->setSkillSelected(false);
    }
    else if (player->ReturnMp() >= 500){
        connect(board, &GameBoard::select,
                this, &Skill3::handleSelection);
        selected = true;
        QPixmap icon(":/resources/gg.png");
        setPixmap(icon);
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
    QPixmap icon(":/resources/g.png");
    setPixmap(icon);
    board->setSkillSelected(false);
    player->GetMP(-500);
    MPBar->setValue(player->ReturnMp());
}
