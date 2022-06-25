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
    QJsonDocument *doc;
    QLabel *dlg, *prologue, *animationLabel;
    QTimer *timer;
    int dlgCount, animationProgress;
    QString animationStr;
    QGraphicsPixmapItem *backgroundMask, *dialogueBackground;
    QFont font;
    bool clicked;
    void setTextAnimation(QLabel *label, const QString &str);


private slots:
    void updateLabel();

};

#endif // DIALOGUE_H
