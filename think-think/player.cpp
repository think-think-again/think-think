#include "player.h"

Player::Player(QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent)
{
    HP = 1000;
    MP = 0;
}

void Player::GetHP(int dHP) {
    HP += dHP;
    if (HP > UpperBoundHp) HP = UpperBoundHp;
    return;
}

void Player::GetMP(int dMP) {
    MP += dMP;
    if (MP > UpperBoundMp) MP = UpperBoundMp;
}
