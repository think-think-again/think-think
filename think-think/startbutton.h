#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class StartButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal myScale
               READ myScale
               WRITE setMyScale
               NOTIFY myScaleChanged)
public:
    StartButton(const QString &name);
    void setMyScale(qreal scale);
    qreal myScale();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();
    void myScaleChanged();

private:
    QPropertyAnimation *zoomInAnimation, *zoomOutAnimation;
};

#endif // STARTBUTTON_H
