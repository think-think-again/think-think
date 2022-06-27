#include "skillhoverlayer.h"

SkillHoverLayer::SkillHoverLayer(const QPixmap &_pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(_pixmap, parent)
{
    hoverDelay = new QTimer(this);
}

void SkillHoverLayer::mousePressEvent(__attribute__((unused))QGraphicsSceneMouseEvent *event)
{
    emit mousePress();
}

void SkillHoverLayer::hoverEnterEvent(__attribute__((unused))QGraphicsSceneHoverEvent *event)
{
    qDebug()<< "Enter";
    if(!hoverDelay->isActive()){
        hoverDelay->setSingleShot(true);
        hoverDelay->start(800);
    }
}

void SkillHoverLayer::hoverLeaveEvent(__attribute__((unused))QGraphicsSceneHoverEvent *event)
{
    hoverDelay->stop();
    emit hoverLeave();
}
