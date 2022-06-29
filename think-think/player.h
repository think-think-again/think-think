#ifndef PLAYER_H
#define PLAYER_H

#include "harmlabel.h"
#include<QGraphicsPixmapItem>
#include<QProgressBar>
class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
   explicit Player(QGraphicsItem* parent = 0);
    const int Attack = 50;
    const int UpperBoundHp = 1000;
    const int UpperBoundMp = 1000;
    int getHP;
    int getMP;
    void GetHP(int dHP);
    void GetMP(int dMP);
    const double UpgradeRateBlue = 3.0;
    const double UpgradeRateRed = 3.0;
    const double UpgradeRateOrange = 1.7;
    const double UpgardeRateGreen = 1.7;
    int ReturnHp();
    int ReturnMp();
    QProgressBar* PlayerHp;
    QProgressBar* PlayerMp;
    double debuff;
    int duration;
private:
    int HP;
    int MP;
signals:
    void harmDisplay(HarmLabel*);
};

#endif // PLAYER_H
