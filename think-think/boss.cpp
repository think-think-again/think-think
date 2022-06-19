#include "boss.h"

Boss::Boss(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    QPixmap bossPixmap(":/resources/boss.jpg");
    setPixmap(bossPixmap);
    setOffset(-958/2,-958/2);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}
