#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "battlescene.h"
#include "dialogue.h"
#include "mainmenu.h"

#include <QStackedLayout>
#include <QWidget>



class MyWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = nullptr);
    QStackedLayout *layout;

private:
    MainMenu *menu;
    Dialogue *dialogue;
    BattleScene *battle;

signals:

public slots:
    void startDialog();
    void startBattle();

};

#endif // MYWINDOW_H
