#ifndef SKILLHOVERLAYER_H
#define SKILLHOVERLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class SkillHoverLayer : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SkillHoverLayer(const QPixmap &_pixmap, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QTimer *hoverDelay;
signals:
    void hoverLeave();
    void mousePress();
};

#endif // SKILLHOVERLAYER_H
