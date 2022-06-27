#ifndef SKILL_H
#define SKILL_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Skill : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Skill(bool _isDirectional = false);
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    bool isDirectional;
signals:
    void clicked();
};

#endif // SKILL_H
