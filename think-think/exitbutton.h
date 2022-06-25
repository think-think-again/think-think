#ifndef EXITBUTTON_H
#define EXITBUTTON_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class ExitButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal scale
               READ scale
               WRITE setScale
               NOTIFY scaleChanged)
public:
    ExitButton();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();
    void scaleChanged();

private:
    QPropertyAnimation *zoomInAnimation, *zoomOutAnimation;
};

#endif // EXITBUTTON_H
