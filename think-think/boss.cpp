#include "boss.h"

#include <QPropertyAnimation>

Boss::Boss(int _difficulty, QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent),
    difficulty(_difficulty)
{
    QPixmap bossPixmap(":/resources/30232-0.7(RGB)(noise_scale)(Level0)(x4.000000).png");
    setPixmap(bossPixmap);
    setScale(0.7);
    setPos(1200, 300);

    floating = new QSequentialAnimationGroup(this);
    QPropertyAnimation *f;
    f = new QPropertyAnimation(this, "pos");
    f->setStartValue(QPointF(1200, 150));
    f->setEndValue(QPointF(1200, 100));
    f->setEasingCurve(QEasingCurve::InOutQuad);
    f->setDuration(2000);
    floating->addAnimation(f);
    f = new QPropertyAnimation(this, "pos");
    f->setStartValue(QPointF(1200, 100));
    f->setEndValue(QPointF(1200, 150));
    f->setEasingCurve(QEasingCurve::InOutQuad);
    f->setDuration(2000);
    floating->addAnimation(f);
    floating->setLoopCount(-1);
    floating->start();

    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    HP = 1500 + difficulty * 1000;
}

void Boss::hurt(int harm){
    HP -= harm;
    return;
}
