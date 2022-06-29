#ifndef HARMLABEL_H
#define HARMLABEL_H

#include <QLabel>
#include <QObject>

class HarmLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(float alpha
               READ alpha
               WRITE setAlpha
               NOTIFY alphaChanged)
public:
    HarmLabel(int harm);
    float alpha();
    void setAlpha(float _alpha);
private:
    float m_alpha;
signals:
    void alphaChanged();
};

#endif // HARMLABEL_H
