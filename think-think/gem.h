#ifndef GEM_H
#define GEM_H

#include <QGraphicsPixmapItem>

enum gemType{ Blue, Green, Red, Orange, gemTypeNum};

class gameBoard;
class Gem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos
               READ pos
               WRITE setPos
               NOTIFY posChanged)
public:
    explicit Gem(gemType type, gameBoard *parent, int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setGPos(int x, int y);

    QPointF pos() const;
    void setPos(const QPointF &pos);

signals:
    void posChanged(QPointF);

private:
    QPointF lastClickPosition;
    bool lastClickHandled;
    gameBoard *board;
    int gx, gy;
    QPointF m_pos;



};

#endif // GEM_H
