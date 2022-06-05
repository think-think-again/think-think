#include "gem.h"

#include <string>

const char *gemTypeName[] = {"blue", "green", "red", "orange"};

Gem::Gem(gemType type, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap((":/resources/64w/" + std::string(gemTypeName[type]) + ".png").c_str());
    pixmap = pixmap.scaled(64, 64);
    setPixmap(pixmap);
    setOffset(-pixmap.width() / 2, -pixmap.height() / 2);
    qDebug() << pixmap.width();
}
