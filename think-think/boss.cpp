#include "boss.h"

Boss::Boss(int _difficulty, QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent),
    difficulty(_difficulty)
{
    QPixmap bossPixmap(":/resources/boss.jpg");
    setPixmap(bossPixmap);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    HP = 1500 + difficulty * 1000;
}

void Boss::hurt(int harm){
    HP -= harm;
    return;
}
