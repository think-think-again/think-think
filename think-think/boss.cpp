#include "boss.h"

Boss::Boss(QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    QPixmap bossPixmap(":/resources/boss.jpg");
    setPixmap(bossPixmap);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}
