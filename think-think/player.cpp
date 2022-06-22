#include "player.h"

Player::Player(QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent)
{
    HP = 1000;
    MP = 0;
}
