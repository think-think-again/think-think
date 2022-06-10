#include "gameboard.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    gameBoard board;
    scene.addItem(&board);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setFixedSize(scene.sceneRect().size().toSize());
//    view.show();

    QWidget window;
    QGridLayout layout(&window);
    layout.addWidget(&view, 0, 0);
    window.showFullScreen();

    return a.exec();
}
