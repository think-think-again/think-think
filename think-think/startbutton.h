#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QGraphicsTextItem>

class startButton : public QGraphicsTextItem
{
    Q_OBJECT
public:
    startButton(const QString &text, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();
};

#endif // STARTBUTTON_H
