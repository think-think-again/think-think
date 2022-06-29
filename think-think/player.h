#ifndef PLAYER_H
#define PLAYER_H

#include<QGraphicsPixmapItem>
class Player: public QObject, public QGraphicsPixmapItem
{
public:
   explicit Player(QGraphicsItem* parent = 0);
    const int Attack = 30;
    const int UpperBoundHp = 1000;
    const int UpperBoundMp = 1000;
    const int getHP = 50;
    const int getMP = 40;
    void GetHP(int dHP);
    void GetMP(int dMP);
    const double UpgradeRateBlue = 3.0;
    const double UpgradeRateRed = 3.0;
    const double UpgradeRateOrange = 1.7;
    const double UpgardeRateGreen = 1.7;
    int ReturnHp();
    int ReturnMp();
private:
    int HP;
    int MP;
};

#endif // PLAYER_H
