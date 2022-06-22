#include "gem.h"
#include "gameboard.h"
#include "battlescene.h"

#include <QGraphicsSceneMouseEvent>
#include <QSequentialAnimationGroup>
#include <string>

Gem::Gem(GemTypes tp, GameBoard *parent, int x, int y)
    : QGraphicsPixmapItem((QGraphicsPixmapItem *)parent),
      type(tp),
      hover(false),
      board(parent),
      gx(x), gy(y),
      dx(0), dy(0),
      curSwapAnimation(nullptr)
{
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
    pixmap = pixmap.scaled(Gem::gemSize*2, Gem::gemSize*2);
    setPixmap(pixmap);
    setOffset(-Gem::gemSize, -Gem::gemSize);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setAcceptHoverEvents(true);
    setScale(defaultScale);

    scaleAnimation = new QPropertyAnimation(this, "scale");
    scaleAnimation->setStartValue(defaultScale);
    scaleAnimation->setKeyValueAt(0.5, defaultScale*scaleFactor);
    scaleAnimation->setEndValue(defaultScale);
    scaleAnimation->setDuration(600);
    scaleAnimation->setLoopCount(-1);
    
    rotateAnimation = new QSequentialAnimationGroup(this);
    QPropertyAnimation *rotate = new QPropertyAnimation(this, "rotation");
    rotate->setStartValue(0);
    rotate->setEndValue(-18);
    rotate->setEasingCurve(QEasingCurve::OutQuad);
    rotate->setDuration(333/4.);
    rotateAnimation->addAnimation(rotate);
    rotate = new QPropertyAnimation(this, "rotation");
    rotate->setStartValue(-18);
    rotate->setEndValue(18);
    rotate->setEasingCurve(QEasingCurve::InOutQuad);
    rotate->setDuration(333/2.);
    rotateAnimation->addAnimation(rotate);
    rotate = new QPropertyAnimation(this, "rotation");
    rotate->setStartValue(18);
    rotate->setEndValue(0);
    rotate->setEasingCurve(QEasingCurve::OutQuad);
    rotate->setDuration(333/4.);
    rotateAnimation->addAnimation(rotate);
    rotateAnimation->setLoopCount(-1);
}

void Gem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastPosition = this->pos();
        scaleAnimation->start();
//        lastClickHandled = false;
    }
}

void Gem::handleMouseRelease()
{
    hover = false;
    rotateAnimation->stop();
    setRotation(0);
    if(curSwapAnimation!=nullptr)
        disconnect(curSwapAnimation, &QParallelAnimationGroup::finished,
                   this, &Gem::handleMouseRelease);
    if(board->existMatching()) board->lazyErase();
    else board->swapGem(gx, gy, gx-dx, gy-dy)->start(QAbstractAnimation::DeleteWhenStopped);
    dx = dy = 0;
}

void Gem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        scaleAnimation->stop();
        setScale(defaultScale);
        if(dx || dy){
            if(curSwapAnimation==nullptr || curSwapAnimation->state() == QAbstractAnimation::Stopped)
                handleMouseRelease();
            else{
                connect(curSwapAnimation, &QParallelAnimationGroup::finished,
                        this, &Gem::handleMouseRelease);
            }
        }
    }
}

void Gem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(curSwapAnimation!=nullptr && curSwapAnimation->state() == QAbstractAnimation::Running) return;
    if(event->buttons() & Qt::LeftButton){
        QPointF delta = event->scenePos() - lastPosition;
        // move forward
        if(dx==0 && dy==0 && (qAbs(delta.x())>gemSize/2 || qAbs(delta.y())>gemSize/2)){
            // moving direction
            int x = 0, y = 0;
            if(qAbs(delta.x())>qAbs(delta.y()))
                x = (delta.x()<0 ? -1 : 1);
            else
                y = (delta.y()<0 ? -1 : 1);
            if(0<=gx+x && gx+x<GameBoard::boardSizeX && 0<=gy+y && gy+y<GameBoard::boardSizeY){
                dx = x, dy = y;
                curSwapAnimation = board->swapGem(gx, gy, gx+x, gy+y);
                curSwapAnimation->start();
            }
        }
        if((dx || dy) && qAbs(delta.x())<=gemSize/2 && qAbs(delta.y())<=gemSize/2){
            // gx and gy here are modified by last swap !!!
            board->swapGem(gx, gy, gx-dx, gy-dy)->start(QAbstractAnimation::DeleteWhenStopped);
            dx = dy = 0;
        }
    }
}

void Gem::hoverEnterEvent(__attribute__ ((unused))QGraphicsSceneHoverEvent *event)
{
    if(!hover){
        hover = true;
        rotateAnimation->start();
    }
}

void Gem::hoverLeaveEvent(__attribute__ ((unused))QGraphicsSceneHoverEvent *event)
{
    if(hover){
        hover = false;
        rotateAnimation->stop();
        setRotation(0);
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
