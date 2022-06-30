#include "myglobalvariants.h"
#include "mywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "0");

    QApplication a(argc, argv);
    QApplication* app = &a;

    QSize screen = QGuiApplication::primaryScreen()->size();
    SCREEN_WIDTH = screen.width();
    SCREEN_HEIGHT = screen.height();
    SCREEN_SCALE = qMin(SCREEN_WIDTH/2560., SCREEN_HEIGHT/1440.);
    BACKGROUND_SCALE = qMax(SCREEN_WIDTH/2560., SCREEN_HEIGHT/1440.);
    MARGIN_HORIZONTAL = round((SCREEN_WIDTH-2560*SCREEN_SCALE)/2);
    MARGIN_VERTICAL = round((SCREEN_HEIGHT-1440*SCREEN_SCALE)/2);
    GEM_SIZE = 128*SCREEN_SCALE;

//    qDebug() << SCREEN_WIDTH << SCREEN_HEIGHT << SCREEN_SCALE;

    MyWindow window(app);
    window.showFullScreen();

    return a.exec();
}
