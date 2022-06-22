#ifndef BOSS_H
#define BOSS_H

#include<QGraphicsPixmapItem>

class Boss:public QObject, public QGraphicsPixmapItem
{
public:
    explicit Boss(int _difficulty, QGraphicsItem* parent = 0);
    void hurt(int harm);
private:
    int HP;
    int difficulty;
};


#endif // BOSS_H
