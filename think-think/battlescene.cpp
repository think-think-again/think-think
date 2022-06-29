#include "battlescene.h"
#include "qscreen.h"
#include "skill1.h"
#include "skill2.h"
#include "skill3.h"
#include "skill4.h"
#include "mywindow.h"

#include <QFile>
#include <QFontDatabase>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGuiApplication>

BattleScene::BattleScene(const QString &name, QObject *parent)
    : QGraphicsScene{parent}
{
    // change to screen resolution
    QSize screenSize = QGuiApplication::primaryScreen()->size();
    screenSize = QSize(2560, 1440);
    setSceneRect(0, 0, screenSize.width(), screenSize.height());

    QPixmap _background(":/resources/classroom1.jpg");
    _background = _background.scaled(2560, 1440, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(_background);
    background->setPos(-(_background.width()-2560)/2, -(_background.height()-1440)/2);
    addItem(background);

    QPixmap _backgroundMask(2560, 1440);
    _backgroundMask.fill(QColor(255, 255, 255, 90));
    backgroundMask = new QGraphicsPixmapItem(_backgroundMask);
    addItem(backgroundMask);

    player = new Player;
    Player* _player = player;

    int dif;
    if(name == "ljy")dif = 1;
    if(name == "zqj")dif = 2;
    if(name == "gw")dif = 3;
    boss = new Boss(name, dif);
    addItem(boss);
    Boss *_boss = boss;

    QPixmap _gameboard_Background(":/resources/gameboard_background.png");
    _gameboard_Background = _gameboard_Background.scaled(2560, 1440, Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *gameboard_background = new QGraphicsPixmapItem(_gameboard_Background);
    gameboard_background->setPos(-(_gameboard_Background.width()-2560)/2, -(_gameboard_Background.height()-1440)/2);
    addItem(gameboard_background);

    board = new GameBoard(_boss, _player);
    connect(board, &GameBoard::turnFinished,
            this, &BattleScene::handleTurnFinished);

    QGraphicsScene *boardScene = new QGraphicsScene;
    boardScene->addItem(board);
    boardScene->setSceneRect(boardScene->sceneRect());

    QGraphicsView *boardView = new QGraphicsView(boardScene);
    boardView->setRenderHint(QPainter::Antialiasing);
    boardView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boardView->setFixedSize(boardScene->sceneRect().size().toSize());
    boardView->setStyleSheet("background: transparent; border:0px");
    QGraphicsProxyWidget *boardProxy = addWidget(boardView);
    boardProxy->setPos(300, 300);

    QProgressBar *BossHpBg = new QProgressBar;
    addWidget(BossHpBg);
    BossHpBg->setOrientation(Qt::Horizontal);
    BossHpBg->setMinimum(0);
    BossHpBg->setMaximum(1);
    BossHpBg->setValue(1);
    BossHpBg->setGeometry(600, 100, 1000, 50);
    BossHpBg->setFormat("");
    BossHpBg->setStyleSheet("QProgressBar{"
                            "    background: transparent;"
                            "    border-radius: 20px;"
                            "}"
                            "QProgressBar::chunk{"
                            "    background: #818181;"
                            "    border-radius: 20px;"
                            "}");

    BossHp = new QProgressBar;
    addWidget(BossHp);
    BossHp->setOrientation(Qt::Horizontal);
    BossHp->setMinimum(0);
    BossHp->setMaximum(boss->GetHp());
    BossHp->setValue(boss->GetHp());
    BossHp->setGeometry(600, 100, 1000, 50);
    BossHp->setFormat(QString::fromLocal8Bit("%v"));
    BossHp->setAlignment(Qt::AlignCenter);
    BossHp->setStyleSheet("QProgressBar{"
                          "    background: transparent;"
                          "    border: 2px solid red;"
                          "    border-radius: 20px;"
                          "    color: white;"
                          "    font-size: 30px;"
                          "}"
                          "QProgressBar::chunk{"
                          "    background: rgb(244, 88, 56);"
                          "    border-radius: 20px;"
                          "}");

    QProgressBar *PlayerHpBg = new QProgressBar;
    addWidget(PlayerHpBg);
    PlayerHpBg->setOrientation(Qt::Horizontal);
    PlayerHpBg->setMinimum(0);
    PlayerHpBg->setMaximum(1);
    PlayerHpBg->setValue(1);
    PlayerHpBg->setGeometry(320, 1440-170, 300, 40);
    PlayerHpBg->setFormat("");
    PlayerHpBg->setStyleSheet("QProgressBar{"
                              "    background: transparent;"
                              "    border-radius: 10px;"
                              "}"
                              "QProgressBar::chunk{"
                              "    background: #818181;"
                              "    border-radius: 10px;"
                              "}");

    PlayerHp = new QProgressBar;
    addWidget(PlayerHp);
    PlayerHp->setOrientation(Qt::Horizontal);
    PlayerHp->setMinimum(0);
    PlayerHp->setMaximum(player->UpperBoundHp);
    PlayerHp->setValue(player->ReturnHp());
    PlayerHp->setGeometry(320, 1440-170, 300, 40);
    PlayerHp->setFormat(QString::fromLocal8Bit("%v"));
    PlayerHp->setAlignment(Qt::AlignCenter);
    PlayerHp->setStyleSheet("QProgressBar{"
                            "    background: transparent;"
                            "    border: 2px solid green;"
                            "    border-radius: 10px;"
                            "    color: yellow;"
                            "    font-size: 20px;"
                            "}"
                            "QProgressBar::chunk{"
                            "    background: green;"
                            "    border-radius: 10px;"
                            "}");

    QProgressBar *PlayerMpBg = new QProgressBar;
    addWidget(PlayerMpBg);
    PlayerMpBg->setOrientation(Qt::Horizontal);
    PlayerMpBg->setMinimum(0);
    PlayerMpBg->setMaximum(1);
    PlayerMpBg->setValue(1);
    PlayerMpBg->setGeometry(320, 1440-100, 300, 40);
    PlayerMpBg->setFormat("");
    PlayerMpBg->setStyleSheet("QProgressBar{"
                              "    background: transparent;"
                              "    border-radius: 10px;"
                              "}"
                              "QProgressBar::chunk{"
                              "    background: #ffffff;"
                              "    border-radius: 10px;"
                              "}");

    PlayerMp = new QProgressBar;
    addWidget(PlayerMp);
    PlayerMp->move(300, 1440-100);
    PlayerMp->setOrientation(Qt::Horizontal);
    PlayerMp->setMinimum(0);
    PlayerMp->setMaximum(player->UpperBoundMp);
    PlayerMp->setValue(0);
    PlayerMp->setGeometry(320, 1440-100, 300, 40);
    PlayerMp->setFormat(QString::fromLocal8Bit("%v"));
    PlayerMp->setAlignment(Qt::AlignCenter);
    PlayerMp->setStyleSheet("QProgressBar{"
                            "    background: transparent;"
                            "    border: 2px solid yellow;"
                            "    border-radius: 10px;"
                            "    color: blue;"
                            "    font-size: 20px;"
                            "}"
                            "QProgressBar::chunk{"
                            "    background: yellow;"
                            "    border-radius: 10px;"
                            "}");

    board->BossHp = BossHp;
    board->PlayerHp = PlayerHp;
    board->PlayerMp = PlayerMp;

    // add returnMenu button
    returnMenu = new StartButton("menu");
    returnMenu->setPos(2560-240, 1440-1360);
    addItem(returnMenu);

    skill[0] = new Skill1(this);
    skill[1] = new Skill2(this);
    skill[2] = new Skill3(this, board, player);
    skill[3] = new Skill4(this, board, player);
    for(int i=0; i<4; ++i){
        addItem(skill[i]);
        connect(skill[i], &Skill::increaseMp,
                this, &BattleScene::increaseMp);
        connect(skill[i], &Skill::increasePlayerHp,
                this, &BattleScene::increasePlayerHp);
        connect(skill[i], &Skill::increaseBossHp,
                this, &BattleScene::increaseBossHp);
        connect(skill[i], &Skill::skillPerformed,
                this, &BattleScene::handleTurnFinished);
        skill[i]->setPos(700+i*150, 1440-200);
    }

    QFile fontFile(":/resources/fonts/FZYanSJW_Zhun.TTF");
    fontFile.open(QIODevice::ReadOnly);
    int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    QFont font;
    font.setFamilies(QFontDatabase::applicationFontFamilies(fontId));
    font.setPixelSize(30);

    RoundNum = new QLabel;
    RoundNum->setFont(font);
    RoundNum->setStyleSheet("QLabel{ background: rgba(170, 0, 0, 0.7); color: white; border-style: outset; border-width: medium; border-color: rgba(170, 0, 0, 0.7);}");
    addWidget(RoundNum);
    RoundNum->setText("回合数：1 / 40");
    RoundNum->move(300, 170);
    board->RoundNum = RoundNum;
//    RoundNum->setMargin(5);
//    RoundNum->setScaledContents(true);

}

void BattleScene::increaseMp(int x)
{
    player->GetMP(x);
    PlayerMp->setValue(player->ReturnMp());
}

void BattleScene::increasePlayerHp(int x)
{
    player->GetHP(x);
    PlayerHp->setValue(player->ReturnHp());
}

void BattleScene::increaseBossHp(int x)
{
    boss->hurt(-x);
    BossHp->setValue(boss->GetHp());
}

void BattleScene::handleTurnFinished()
{
    if (board->T > 40 || player->ReturnHp() == 0) {
        emit battleFailed();
    }
    if (boss->GetHp() == 0) {
        emit battleSucceeded();
    }
}
