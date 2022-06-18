#ifndef MAINMENU_H
#define MAINMENU_H

#include "startbutton.h"

#include <QGraphicsScene>

class myWindow;
class mainMenu : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit mainMenu(myWindow *parent);

private:
    QGraphicsPixmapItem *background;
    startButton *startGame;
    myWindow *window;

private slots:
};

#endif // MAINMENU_H
