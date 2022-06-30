#include "harmlabel.h"
#include "myglobalvariants.h"

HarmLabel::HarmLabel(int harm, const QString &_color)
    : QLabel((harm>=0?"+":"") + QString::number(harm))
{
    if(_color == "") color = (harm>=0 ? "0, 170, 0" : "170, 0, 0");
    else color = _color;
    m_alpha = 1;
    setStyleSheet("QLabel{ background: transparent; font-style: italic; color: rgba(" + color + ", 1); font-size: " + QString::number((int)(100*SCREEN_SCALE)) + "px;}");
}

float HarmLabel::alpha()
{
    return m_alpha;
}

void HarmLabel::setAlpha(float _alpha)
{
    if(_alpha != m_alpha){
        m_alpha = _alpha;
        setStyleSheet("QLabel{ background: transparent; font-style: italic; color: rgba(" + color + ", " + QString::number(_alpha) + "); font-size: " + QString::number((int)(100*SCREEN_SCALE)) + "px;}");
        emit alphaChanged();
    }
}
