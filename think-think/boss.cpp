#include "boss.h"
#include "harmlabel.h"

#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

Boss::Boss(const QString &name, int _difficulty, QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent),
    difficulty(_difficulty),
    joy(20030206)
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
    HarmLabel *harmLabel = new HarmLabel(-harm);
    emit harmDisplay(harmLabel);
    QParallelAnimationGroup *harmAnimation = new QParallelAnimationGroup;
    QPropertyAnimation *ascend = new QPropertyAnimation(harmLabel, "pos");
    int x = joy()%400+1800, y = joy()%800+400;
    ascend->setStartValue(QPoint(x, y));
    ascend->setEndValue(QPoint(x, y-200));
    ascend->setDuration(1000);
    ascend->setEasingCurve(QEasingCurve::OutQuad);
    harmAnimation->addAnimation(ascend);
    QPropertyAnimation *fadeOut = new QPropertyAnimation(harmLabel, "alpha");
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);
    fadeOut->setDuration(2000);
    harmAnimation->addAnimation(fadeOut);

    connect(harmAnimation, &QParallelAnimationGroup::finished,
            harmLabel, &HarmLabel::deleteLater);
    harmAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    HP -= harm;
    if (HP < 0) HP = 0;
    return;
}

int Boss::GetHp()
{
    return HP;
}
