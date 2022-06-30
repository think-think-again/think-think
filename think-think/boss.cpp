#include "boss.h"
#include "harmlabel.h"
#include "myglobalvariants.h"

#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

Boss::Boss(const QString &name, int _difficulty, QGraphicsItem* parent)
    :QGraphicsPixmapItem(parent),
    difficulty(_difficulty),
    joy(20030206)
{
    QPixmap bossPixmap(":/resources/character/" + name + ".png");
    bossPixmap = bossPixmap.scaled(bossPixmap.size()*SCREEN_SCALE);
    setPixmap(bossPixmap);
    setScale(0.7);
    setPos(1200*SCREEN_SCALE+MARGIN_HORIZONTAL, 150*SCREEN_SCALE+MARGIN_VERTICAL*2);

    floating = new QSequentialAnimationGroup(this);
    QPropertyAnimation *f;
    f = new QPropertyAnimation(this, "pos");
    f->setStartValue(QPointF(1200*SCREEN_SCALE+MARGIN_HORIZONTAL, 150*SCREEN_SCALE+MARGIN_VERTICAL*2));
    f->setEndValue(QPointF(1200*SCREEN_SCALE+MARGIN_HORIZONTAL, 100*SCREEN_SCALE+MARGIN_VERTICAL*2));
    f->setEasingCurve(QEasingCurve::InOutQuad);
    f->setDuration(2000);
    floating->addAnimation(f);
    f = new QPropertyAnimation(this, "pos");
    f->setStartValue(QPointF(1200*SCREEN_SCALE+MARGIN_HORIZONTAL, 100*SCREEN_SCALE+MARGIN_VERTICAL*2));
    f->setEndValue(QPointF(1200*SCREEN_SCALE+MARGIN_HORIZONTAL, 150*SCREEN_SCALE+MARGIN_VERTICAL*2));
    f->setEasingCurve(QEasingCurve::InOutQuad);
    f->setDuration(2000);
    floating->addAnimation(f);
    floating->setLoopCount(-1);
    floating->start();

    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    HP = 1500 + difficulty * 1000;
    UpperBoundHp = HP;
    PhysicalDefense = 5 + _difficulty * 5;
    MagicalDefense = 8 + _difficulty * 4;
}

void Boss::hurt(int harm){
    HarmLabel *harmLabel = new HarmLabel(-harm);
    emit harmDisplay(harmLabel);
    QParallelAnimationGroup *harmAnimation = new QParallelAnimationGroup;
    QPropertyAnimation *ascend = new QPropertyAnimation(harmLabel, "pos");
    int x = joy()%400+1800, y = joy()%800+400;
    ascend->setStartValue(QPoint(x*SCREEN_SCALE+MARGIN_HORIZONTAL, y*SCREEN_SCALE+MARGIN_VERTICAL*2));
    ascend->setEndValue(QPoint(x*SCREEN_SCALE+MARGIN_HORIZONTAL, (y-200)*SCREEN_SCALE+MARGIN_VERTICAL*2));
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
int Boss::getPD()
{
    return PhysicalDefense;
}
int Boss::getMD()
{
    return MagicalDefense;
}

void Boss::Skill()
{
    if (BossSkillId == 0)
    {
        int dHp = difficulty * 50 + 150;
        player->GetHP(-1 * dHp);
        player->PlayerHp->setValue(player->ReturnHp());
    }
    else if (BossSkillId == 1)
    {
        int dMp = difficulty * 30 + 50;
        player->GetMP(-1 * dMp);
        player->PlayerMp->setValue(player->ReturnMp());
    }
    else if (BossSkillId == 2)
    {
        int dHp = 50 + difficulty * 50;
        player->GetHP(-1 * dHp);
        HP += 50 + difficulty * 50;
        if (HP > UpperBoundHp) HP = UpperBoundHp;
        BossHp->setValue(HP);
        player->PlayerHp->setValue(player->ReturnHp());
    }
    else if (BossSkillId == 3)
    {
        player->debuff = 1 - difficulty * 0.1;
        player->duration = 5;
    }

}
