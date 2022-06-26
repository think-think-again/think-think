#include "gameboard.h"
#include "mainmenu.h"
#include "mywindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QStackedLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication* app = &a;

    MyWindow window(app);
    window.showFullScreen();

    return a.exec();
}
