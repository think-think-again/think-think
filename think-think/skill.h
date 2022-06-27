#ifndef SKILL_H
#define SKILL_H

#include "player.h"
#include "skillhoverlayer.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QObject>
#include <QTimer>

class BattleScene;
class Skill : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Skill(BattleScene *_scene, const QString &_introduction, bool _isDirectional = false);
    void setPos(qreal x, qreal y);
    QString introduction;
    bool isDirectional;
    QLabel *introductionLabel;
    QGraphicsProxyWidget *introductionLabelProxy;
    QGraphicsPixmapItem *icon;
private:
    SkillHoverLayer *layer;
    BattleScene *scene;
    QFont font;
signals:
    void clicked();
public slots:
    void showIntroduction();
    void hideIntroduction();
    virtual void handleMousePress() = 0;
};

#endif // SKILL_H
