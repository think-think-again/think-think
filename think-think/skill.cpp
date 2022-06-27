#include "skill.h"

Skill::Skill(bool _isDirectional)
    : isDirectional(_isDirectional)
{
    QPixmap icon(":/resources/g.png");
    setPixmap(icon);
    setScale(1./3);
    setAcceptHoverEvents(true);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}
