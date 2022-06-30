#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "battlescene.h"
#include "dialogue.h"
#include "mainmenu.h"

#include <QStackedLayout>
#include <QWidget>
#include <QApplication>
#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>



class MyWindow : public QWidget
{
    static constexpr char bossNames[][4] = {"ljy", "zqj", "gw"};

    Q_OBJECT
public:
    explicit MyWindow(QApplication *_app, QWidget *parent = nullptr);
    QStackedLayout *layout;
    QApplication *app;
private:
    QGraphicsView *initMainMenu();
    QGraphicsView *initDialogue(int bossId);
    QGraphicsView *initBattle(int bossId);
    MainMenu *menu;
    Dialogue *dialogue;
    BattleScene *battle;
    int currentBossId;
    QGraphicsOpacityEffect *battleOpacity;
    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;

signals:

public slots:
    void startDialogue();
    void startBattle();
    void returnMenu();
    void handleBattleFailed();
    void handleBattleSucceeded();
    void playMusicAgain();
};

#endif // MYWINDOW_H
