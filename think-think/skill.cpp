#include "skill.h"
#include "battlescene.h"

#include <QFile>
#include <QFontDatabase>

Skill::Skill(BattleScene *_scene, const QString &_introduction, bool _isDirectional)
    : scene(_scene),
      introduction(_introduction),
      isDirectional(_isDirectional)
{
    QPixmap _icon(":/resources/g.png");
    icon = new QGraphicsPixmapItem(_icon);
    icon->setZValue(0);
    scene->addItem(icon);
    _icon.fill(QColor(0, 0, 0, 0));
    layer = new SkillHoverLayer(_icon);
    layer->setZValue(3);
    layer->setAcceptHoverEvents(true);
    layer->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    scene->addItem(layer);
//    qDebug() << "layer Z: " << layer->zValue();
    icon->setScale(1./3);
    layer->setScale(1./3);

    connect(layer->hoverDelay, &QTimer::timeout,
            this, &Skill::showIntroduction);
    connect(layer, &SkillHoverLayer::hoverLeave,
            this, &Skill::hideIntroduction);
    connect(layer, &SkillHoverLayer::mousePress,
            this, &Skill::handleMousePress);

    QFile fontFile(":/resources/FZYanSJW_Zhun.TTF");
    fontFile.open(QIODevice::ReadOnly);
    int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    font.setFamilies(QFontDatabase::applicationFontFamilies(fontId));
    font.setPixelSize(30);

    introductionLabel = new QLabel(_introduction);
    introductionLabel->setFont(font);
    introductionLabel->setStyleSheet("QLabel{ background: rgba(170, 0, 0, 0.3); color: white; border-style: outset; border-width: medium; border-color: rgba(170, 0, 0, 0.7);}");
    introductionLabel->hide();
    introductionLabelProxy = scene->addWidget(introductionLabel);
    introductionLabelProxy->setZValue(2);
    //    qDebug() << "label Z: " << introductionLabelProxy->zValue();
}

void Skill::setPos(qreal x, qreal y)
{
    QGraphicsPixmapItem::setPos(x, y);
    icon->setPos(x, y);
    layer->setPos(x, y);
}

void Skill::showIntroduction()
{
    if(layer->hoverDelay->interval() == 800){
        layer->hoverDelay->setSingleShot(false);
        layer->hoverDelay->start(4);
    }
    introductionLabel->show();
    QPoint pos = QCursor::pos();
    pos.setY(pos.y() - introductionLabel->height());
    introductionLabelProxy->setPos(pos);
}

void Skill::hideIntroduction()
{
    introductionLabel->hide();
}
