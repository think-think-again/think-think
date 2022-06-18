#include "startbutton.h"

startButton::startButton(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent)
{

}


void startButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}
