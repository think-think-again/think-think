#ifndef MAINMENU_H
#define MAINMENU_H

#include "startbutton.h"

#include <QGraphicsScene>

class MyWindow;
class MainMenu : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MainMenu(MyWindow *parent);

private:
    QGraphicsPixmapItem *background;
    StartButton *startGame;
    MyWindow *window;

private slots:
};

#endif // MAINMENU_H
