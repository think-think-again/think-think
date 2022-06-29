#ifndef BOSS_H
#define BOSS_H

#include "harmlabel.h"

#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QSequentialAnimationGroup>
#include <time.h>
#include <random>

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

private:
    QSequentialAnimationGroup *floating;
    int HP;
    int difficulty;
    std::mt19937 joy;

signals:
    void posChanged(QPointF);
    void harmDisplay(HarmLabel*);

};


#endif // BOSS_H
