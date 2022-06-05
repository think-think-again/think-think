#include "gameboard.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene scene;
    gameBoard *board = new gameBoard();
    scene.addItem(board);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setFixedSize(scene.sceneRect().size().toSize());
    view.show();
    return a.exec();
}
