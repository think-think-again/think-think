#ifndef GEM_H
#define GEM_H

#include <QGraphicsPixmapItem>

enum gemType{ Blue, Green, Red, Orange, gemTypeNum};

class Gem : public QGraphicsPixmapItem
{
public:
    explicit Gem(gemType type, QGraphicsItem *parent = 0);
};

#endif // GEM_H
