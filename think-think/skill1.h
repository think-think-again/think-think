#ifndef SKILL1_H
#define SKILL1_H

#include "skill.h"
#include <QObject>

class Skill1 : public Skill
{
    Q_OBJECT
public:
    Skill1();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SKILL1_H
