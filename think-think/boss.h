#ifndef BOSS_H
#define BOSS_H

#include<QGraphicsPixmapItem>

class Boss:public QObject, public QGraphicsPixmapItem
{
public:
    explicit Boss(QGraphicsItem* parent = 0);
};


#endif // BOSS_H
