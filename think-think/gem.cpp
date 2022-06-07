#include "gem.h"
#include "gameboard.h"

#include <QGraphicsSceneMouseEvent>
#include <string>

Gem::Gem(GemTypes tp, gameBoard *parent, int x, int y)
    : QGraphicsPixmapItem((QGraphicsPixmapItem *)parent),
      type(tp),
      board(parent),
      gx(x), gy(y)
{
//    qDebug() << "new Gem" << x << y;
    auto gemTypeName = [](GemTypes tp){
        if(tp == Blue) return ":/resources/b.png";
        if(tp == Green) return ":/resources/g.png";
        if(tp == Red) return ":/resources/r.png";
        if(tp == Orange) return ":/resources/o.png";
        if(tp == (Blue | Upgraded)) return ":/resources/bb.png";
        if(tp == (Green | Upgraded)) return ":/resources/gg.png";
        if(tp == (Red | Upgraded)) return ":/resources/rr.png";
        if(tp == (Orange | Upgraded)) return ":/resources/oo.png";
        if(tp == Super) return ":/resources/s.png";
        qCritical() << "invalid gem type";
        return "invalid";
    };
    QPixmap pixmap(gemTypeName(tp));
    pixmap = pixmap.scaled(64, 64);
    setPixmap(pixmap);
    setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
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
            board->dragGem(gx, gy, x, y);
        }
    }
}

void Gem::setGPos(int x, int y)
{
    gx = x, gy = y;
}

GemTypes Gem::getType() const
{
    return type;
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
