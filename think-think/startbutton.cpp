#include "startbutton.h"

StartButton::StartButton()
{
    QPixmap start(":/resources/start.png");
    start = start.scaled(643, 401);
    setPixmap(start);
    setScale(1./3);
    setOffset(-643/3, -401/3);
    setAcceptHoverEvents(true);

    zoomInAnimation = new QPropertyAnimation(this, "scale");
    zoomInAnimation->setStartValue(1./3);
    zoomInAnimation->setEndValue(0.4);
    zoomInAnimation->setDuration(200);

    zoomOutAnimation = new QPropertyAnimation(this, "scale");
    zoomOutAnimation->setStartValue(0.4);
    zoomOutAnimation->setEndValue(1./3);
    zoomOutAnimation->setDuration(200);
}

void StartButton::mousePressEvent(__attribute__ ((unused))QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void StartButton::hoverEnterEvent(__attribute__ ((unused))QGraphicsSceneHoverEvent *event)
{
    zoomInAnimation->start();
}

void StartButton::hoverLeaveEvent(__attribute__ ((unused))QGraphicsSceneHoverEvent *event)
{
    zoomOutAnimation->start();
}
