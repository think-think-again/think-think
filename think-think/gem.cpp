#include "gem.h"
#include "gameboard.h"
#include "battlescene.h"
#include "myglobalvariants.h"
#include <QDebug>
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
        if(tp == Blue) return ":/resources/gems/b.png";
        if(tp == Green) return ":/resources/gems/g.png";
        if(tp == Red) return ":/resources/gems/r.png";
        if(tp == Orange) return ":/resources/gems/o.png";
        if(tp == (Blue | Upgraded)) return ":/resources/gems/bb.png";
        if(tp == (Green | Upgraded)) return ":/resources/gems/gg.png";
        if(tp == (Red | Upgraded)) return ":/resources/gems/rr.png";
        if(tp == (Orange | Upgraded)) return ":/resources/gems/oo.png";
        if(tp == Super) return ":/resources/gems/s.png";
        qCritical() << "invalid gem type";
        return "invalid";
    };
    boss = parent->boss;
    HPBar = parent->BossHp;
    QPixmap pixmap(gemTypeName(tp));
    pixmap = pixmap.scaled(GEM_SIZE*2, GEM_SIZE*2);
    setPixmap(pixmap);
    setOffset(-GEM_SIZE, -GEM_SIZE);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setAcceptHoverEvents(true);
    setScale(defaultScale);
    setPos(x*GEM_SIZE, y*GEM_SIZE);

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
    if(BAN_MOUSE_EVENTS) return;
    if(event->button() == Qt::LeftButton){
        lastPosition = this->pos();
        scaleAnimation->start();
//        lastClickHandled = false;
    }
    else if(event->button() == Qt::RightButton && type == Super){
        board->removeGem(gx, gy);
        board->lazyErase(true);
        boss->hurt(300);
        HPBar->setValue(boss->GetHp());
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
    if(board->existMatching())
    {
        board->T++;
        board->RoundNum->setText("回合数：" + QString::number(board->T) + " / 40");
        board->RoundNum->adjustSize();
        board->lazyErase();
        if (board->player->duration > 0) board->player->duration--;
        else if (board->player->duration == 0) board->player->debuff = 1;
        board->SkillToGo--;
        if (board->SkillToGo == 0){
            emit board->turnBossSkill();
            board->BossSkillId = board->RandomNum();
            board->SkillToGo = board->BossSkillTime[board->BossSkillId];
            boss->BossSkillId = board->BossSkillId;
            board->BossSkillIntroduction->setText(QString::number(boss->BossSkillId)+" "+QString::number(board->SkillToGo));
            if (boss->BossSkillId == 0)
            {
                board->BossSkillIntroduction->setText("对玩家造成"+QString::number(boss->difficulty * 50 + 150) + "点伤害");
            }
            else if (boss->BossSkillId == 1)
            {
                board->BossSkillIntroduction->setText("偷取玩家"+QString::number(50 + 30 * boss->difficulty) + "点精神力");
            }
            else if (boss->BossSkillId == 2)
            {
                board->BossSkillIntroduction->setText("吸取玩家"+QString::number(50 + 50 * boss->difficulty) + "点生命值");
            }
            else if (boss->BossSkillId == 3)
            {
                board->BossSkillIntroduction->setText("降低玩家"+QString::number(10 * boss->difficulty) + "%攻击力，持续5回合");
            }
            board->BossSkillIntroduction->adjustSize();
        }
        for(int i = 0;i < 4;i++){
            if(board->SkillsToGo[i] != 1){
                board->SkillsToGo[i]--;
            }
            else if(board->SkillsToGo[i] == 1){
                if(i == 0) emit board->skillshowed1();
                if(i == 1) emit board->skillshowed2();
                if(i == 2) emit board->skillshowed3();
                if(i == 3) emit board->skillshowed4();
                board->SkillsToGo[i]--;
            }
        }
        //qDebug() << board->T;
    }
    else board->swapGem(gx, gy, gx-dx, gy-dy)->start(QAbstractAnimation::DeleteWhenStopped);
    dx = dy = 0;
}

void Gem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(BAN_MOUSE_EVENTS) return;
    if(event->button() == Qt::LeftButton){
        scaleAnimation->stop();
        setScale(defaultScale);
        if(board->skillSelected()){
//            qDebug() << "gem" << gx << gy << "selected";
            board->emitSelection(gx, gy);
        }
        else{
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
}

void Gem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(BAN_MOUSE_EVENTS) return;
    if(board->skillSelected()) return;
    if(curSwapAnimation!=nullptr && curSwapAnimation->state() == QAbstractAnimation::Running) return;
    if(event->buttons() & Qt::LeftButton){
        QPointF delta = event->scenePos() - lastPosition;
        // move forward
        if(dx==0 && dy==0 && (qAbs(delta.x())>GEM_SIZE/2 || qAbs(delta.y())>GEM_SIZE/2)){
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
        if((dx || dy) && qAbs(delta.x())<=GEM_SIZE/2 && qAbs(delta.y())<=GEM_SIZE/2){
            // gx and gy here are modified by last swap !!!
            board->swapGem(gx, gy, gx-dx, gy-dy)->start(QAbstractAnimation::DeleteWhenStopped);
            dx = dy = 0;
        }
    }
}

void Gem::hoverEnterEvent(__attribute__((unused))QGraphicsSceneHoverEvent *event)
{
    if(BAN_MOUSE_EVENTS) return;
    if(!hover){
        hover = true;
        rotateAnimation->start();
    }
}

void Gem::hoverLeaveEvent(__attribute__((unused))QGraphicsSceneHoverEvent *event)
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
