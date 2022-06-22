#ifndef PLAYER_H
#define PLAYER_H

#include<QGraphicsPixmapItem>
class Player: public QObject, public QGraphicsPixmapItem
{
public:
   explicit Player(QGraphicsItem* parent = 0);
    const int PhysicalAttack = 50;
    const int MagicalAttack = 50;
private:
    int HP;
    int MP;
};

#endif // PLAYER_H
