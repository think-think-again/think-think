#ifndef BOSS_H
#define BOSS_H

#include "harmlabel.h"
#include "player.h"

#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QSequentialAnimationGroup>
#include <time.h>
#include <random>
#include <QProgressBar>

class Boss:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos
               READ pos
               WRITE setPos
               NOTIFY posChanged)

public:
    explicit Boss(const QString &name, int _difficulty, QGraphicsItem* parent = 0);
    void hurt(int harm);
    int GetHp();
    int getPD();
    int getMD();
    Player* player;
    int BossSkillId;
    int difficulty;
    QProgressBar* BossHp;
    QSequentialAnimationGroup *floating;

private:
    int HP;
    int UpperBoundHp;
    std::mt19937 joy;
    int PhysicalDefense;
    int MagicalDefense;


signals:
    void posChanged(QPointF);
    void harmDisplay(HarmLabel*);
public slots:
    void Skill();
};


#endif // BOSS_H
