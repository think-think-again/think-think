#ifndef BOSS_H
#define BOSS_H

#include <QGraphicsPixmapItem>
#include <QSequentialAnimationGroup>

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

signals:
    void posChanged(QPointF);

};


#endif // BOSS_H
