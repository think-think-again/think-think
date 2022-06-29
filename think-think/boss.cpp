#include "boss.h"

#include <QPropertyAnimation>

Boss::Boss(const QString &name, int _difficulty, QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent),
    difficulty(_difficulty)
{
    QPixmap bossPixmap(":/resources/character/" + name + ".png");
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
    if (HP < 0) HP = 0;
    return;
}

int Boss::GetHp()
{
    return HP;
}
