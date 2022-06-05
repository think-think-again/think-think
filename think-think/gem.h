#ifndef GEM_H
#define GEM_H

#include <QGraphicsPixmapItem>

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

class gameBoard;
// TODO: QObject affects performance. Should find an alternative.
class Gem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos
               READ pos
               WRITE setPos
               NOTIFY posChanged)
public:
    explicit Gem(GemTypes type, gameBoard *parent, int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setGPos(int x, int y);
    GemTypes getType() const;

    QPointF pos() const;
    void setPos(const QPointF &pos);

signals:
    void posChanged(QPointF);

private:
    GemTypes type;
    QPointF lastClickPosition;
    bool lastClickHandled;
    gameBoard *board;
    int gx, gy;
    QPointF m_pos;



};

#endif // GEM_H
