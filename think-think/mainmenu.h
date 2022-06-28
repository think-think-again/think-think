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
    explicit MainMenu(QObject *parent);
    StartButton *startGame, *exitGame;
private:
    QGraphicsPixmapItem *background;
private slots:
};

#endif // MAINMENU_H
