#include "harmlabel.h"
#include "myglobalvariants.h"
#include "player.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

Player::Player()
{
    HP = 1000;
    MP = 0;
    debuff = 1;
    getHP = Attack * 4 / 5;
    getMP = Attack * 4 / 5;
}

void Player::GetHP(int dHP) {
    HarmLabel *harmLabel = new HarmLabel(dHP);
    emit harmDisplay(harmLabel);
    QParallelAnimationGroup *harmAnimation = new QParallelAnimationGroup;
    QPropertyAnimation *ascend = new QPropertyAnimation(harmLabel, "pos");
    int x = 50*SCREEN_SCALE+MARGIN_HORIZONTAL, y = SCREEN_HEIGHT-100*SCREEN_SCALE;
    ascend->setStartValue(QPoint(x, y));
    ascend->setEndValue(QPoint(x, y-200*SCREEN_SCALE));
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

    HP += dHP;
    if (HP < 0) HP = 0;
    if (HP > UpperBoundHp) HP = UpperBoundHp;
    return;
}

void Player::GetMP(int dMP) {
    HarmLabel *harmLabel = new HarmLabel(dMP, "255, 255, 0");
    emit harmDisplay(harmLabel);
    QParallelAnimationGroup *harmAnimation = new QParallelAnimationGroup;
    QPropertyAnimation *ascend = new QPropertyAnimation(harmLabel, "pos");
    int x = 50*SCREEN_SCALE+MARGIN_HORIZONTAL, y = SCREEN_HEIGHT-100*SCREEN_SCALE;
    ascend->setStartValue(QPoint(x, y));
    ascend->setEndValue(QPoint(x, y-200*SCREEN_SCALE));
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

    MP += dMP;
    if (MP < 0) MP = 0;
    if (MP > UpperBoundMp) MP = UpperBoundMp;
    return;
}

int Player::ReturnHp()
{
    return HP;
}

int Player::ReturnMp()
{
    return MP;
}
