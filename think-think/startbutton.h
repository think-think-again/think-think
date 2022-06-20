#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class StartButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal scale
               READ scale
               WRITE setScale
               NOTIFY scaleChanged)
public:
    StartButton();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();
    void scaleChanged();

private:
    QPropertyAnimation *zoomInAnimation, *zoomOutAnimation;
};

#endif // STARTBUTTON_H
