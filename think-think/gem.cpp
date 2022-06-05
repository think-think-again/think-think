#include "gem.h"
#include "gameboard.h"

#include <QGraphicsSceneMouseEvent>
#include <string>

const char *gemTypeName[] = {"blue", "green", "red", "orange"};

Gem::Gem(gemType type, gameBoard *parent, int x, int y)
    : QGraphicsPixmapItem((QGraphicsPixmapItem *)parent),
      board(parent),
      gx(x), gy(y)
{
    QPixmap pixmap((":/resources/64w/" + std::string(gemTypeName[type]) + ".png").c_str());
    pixmap = pixmap.scaled(64, 64);
    setPixmap(pixmap);
    setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
//    qDebug() << pixmap.width();
}

void Gem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastClickPosition = event->pos();
        lastClickHandled = false;
    }
}

void Gem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastClickHandled = true;
    }
}

void Gem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        if(lastClickHandled) return;
        QPointF delta = event->pos() - lastClickPosition;
        if(qAbs(delta.x())>30 || qAbs(delta.y())>30){
            lastClickHandled = true;
            // moving direction
            int x = 0, y = 0;
            if(qAbs(delta.x())>qAbs(delta.y()))
                x = (delta.x()<0 ? -1 : 1);
            else
                y = (delta.y()<0 ? -1 : 1);
            board->gemMove(gx, gy, x, y);
        }
    }
}

void Gem::setGPos(int x, int y)
{
    gx = x, gy = y;
}

QPointF Gem::pos() const
{
    return m_pos;
}

void Gem::setPos(const QPointF &pos)
{
    m_pos = pos;
    QGraphicsPixmapItem::setPos(pos);
    emit posChanged(pos);
}
