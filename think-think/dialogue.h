#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QGraphicsScene>
#include <QLabel>
#include <QWidget>

class Dialogue : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Dialogue(QObject *parent, const QString &name);
    void initialize();
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void dialogueEnded();

private:
    void setTextAnimation(QLabel *label, const QString &str);
    QJsonDocument *doc;
    QLabel *dlg, *prologue, *animationLabel, *speaker;
    QTimer *timer;
    int dlgCount, animationProgress;
    QString animationStr;
    QGraphicsPixmapItem *backgroundMask, *dialogueBackground, *dialogueBackgroundBoss, *dialogueBackgroundZ;
    QFont font;
    bool clicked;
    QString bossName;


private slots:
    void updateLabel();

};

#endif // DIALOGUE_H
