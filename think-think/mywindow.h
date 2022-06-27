#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "battlescene.h"
#include "dialogue.h"
#include "mainmenu.h"

#include <QStackedLayout>
#include <QWidget>
#include <QApplication>



class MyWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MyWindow(QApplication *_app, QWidget *parent = nullptr);
    QStackedLayout *layout;
    QApplication *app;
private:
    MainMenu *menu;
    Dialogue *dialogue;
    BattleScene *battle;

signals:

public slots:
    void startDialog();
    void startBattle();
    void returnMenu();
};

#endif // MYWINDOW_H
