#include "startbutton.h"

StartButton::StartButton(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent)
{

}


void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}
