#ifndef SKILL2_H
#define SKILL2_H

#include "skill.h"
#include <QObject>

class Skill2 : public Skill
{
    Q_OBJECT
public:
    Skill2();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SKILL2_H
