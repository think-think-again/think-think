#include "myglobalvariants.h"
#include "mywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication* app = &a;

    QRect screen = QGuiApplication::primaryScreen()->geometry();
    SCREEN_WIDTH = screen.width();
    SCREEN_HEIGHT = screen.height();
    SCREEN_SCALE = qMin(SCREEN_WIDTH/2560., SCREEN_HEIGHT/1440.);

    MyWindow window(app);
    window.showFullScreen();

    return a.exec();
}
