#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QLabel>
#include <QWidget>

class Dialogue : public QWidget
{
    Q_OBJECT
public:
    explicit Dialogue(QWidget *parent, const QString &name);

signals:
    void dialogueEnded();

private:
    QJsonDocument *doc;
    QLabel *dlg, *prologue;
    int dlgCount;

private slots:
    void handleButtonClick();

};

#endif // DIALOGUE_H
