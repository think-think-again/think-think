#include "exitbutton.h"

ExitButton::ExitButton()
{
    QPixmap exit(":/resources/exit.png");
    exit = exit.scaled(643, 401);
    setPixmap(exit);
    setScale(1./3);
    setOffset(-1020/3, -1263/3);
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

void ExitButton::mousePressEvent(__attribute__ ((unused))QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void ExitButton::hoverEnterEvent(__attribute__ ((unused))QGraphicsSceneHoverEvent *event)
{
    zoomInAnimation->start();
}

void ExitButton::hoverLeaveEvent(__attribute__ ((unused))QGraphicsSceneHoverEvent *event)
{
    zoomOutAnimation->start();
}

