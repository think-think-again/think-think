#ifndef GEM_H
#define GEM_H

#include <QGraphicsPixmapItem>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QProgressBar>

#include "boss.h"
enum GemType{
    Invalid       = 0x00000000,
    Blue          = 0x00000001,
    Green         = 0x00000002,
    Red           = 0x00000004,
    Orange        = 0x00000008,
    Super         = 0x00000010,
    Upgraded      = 0x00000020,
    BasicGemMask  = 0x0000001f
};
Q_DECLARE_FLAGS(GemTypes, GemType)
Q_DECLARE_OPERATORS_FOR_FLAGS(GemTypes)

class GameBoard;
// TODO: QObject affects performance. Should find an alternative.
class Gem : public QObject, public QGraphicsPixmapItem
{
public:
    static constexpr int gemSize = 128;
    static constexpr double defaultScale = 0.4, scaleFactor = 1.3;

    Q_OBJECT
    Q_PROPERTY(QPointF pos
               READ pos
               WRITE setPos
               NOTIFY posChanged)
    Q_PROPERTY(qreal rotation
               READ rotation
               WRITE setRotation
               NOTIFY rotationChanged)
    Q_PROPERTY(qreal scale
               READ scale
               WRITE setScale
               NOTIFY scaleChanged)
public:
    explicit Gem(GemTypes type, GameBoard *parent, int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void setGPos(int x, int y);
    GemTypes getType() const;

signals:
    void posChanged(QPointF);
    void rotationChanged(qreal);
    void scaleChanged(qreal);


private:
    Boss *boss;
    QProgressBar *HPBar;
    GemTypes type;
    QPointF lastPosition;
    bool lastClickHandled;
    bool hover;
    GameBoard *board;
    int gx, gy, dx, dy;
    QPointF m_pos;
    QPropertyAnimation *scaleAnimation;
    QSequentialAnimationGroup *rotateAnimation;
    QParallelAnimationGroup *curSwapAnimation;
    void handleMouseRelease();
};

#endif // GEM_H
