#include "startbutton.h"

StartButton::StartButton(const QString &name)
{
    QPixmap start(":/resources/" + name + ".png");
    setPixmap(start);
    setMyScale(1./3);
    setAcceptHoverEvents(true);

    zoomInAnimation = new QPropertyAnimation(this, "myScale");
    zoomInAnimation->setStartValue(1./3);
    zoomInAnimation->setEndValue(0.4);
    zoomInAnimation->setDuration(200);

    zoomOutAnimation = new QPropertyAnimation(this, "myScale");
    zoomOutAnimation->setStartValue(0.4);
    zoomOutAnimation->setEndValue(1./3);
    zoomOutAnimation->setDuration(200);
}

void StartButton::setMyScale(qreal scale)
{
    setScale(scale);
    setOffset(-pixmap().width()*scale*0.5, -pixmap().height()*scale*0.5);
}

qreal StartButton::myScale()
{
    return scale();
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
