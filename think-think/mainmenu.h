#ifndef MAINMENU_H
#define MAINMENU_H

#include "startbutton.h"
#include <QGraphicsScene>
#include <QApplication>

class MyWindow;
class MainMenu : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MainMenu(MyWindow *parent);
private:
    QApplication *app;
    QGraphicsPixmapItem *background;
    StartButton *startGame, *exitGame;
    MyWindow *window;

private slots:
};

#endif // MAINMENU_H
