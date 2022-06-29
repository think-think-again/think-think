#include "harmlabel.h"

HarmLabel::HarmLabel(int harm)
    : QLabel("-" + QString::number(harm))
{
    m_alpha = 1;
    setStyleSheet("QLabel{ background: transparent; font-style: italic; color: rgba(170, 0, 0, 1); font-size: 100px;}");
}

float HarmLabel::alpha()
{
    return m_alpha;
}

void HarmLabel::setAlpha(float _alpha)
{
    if(_alpha != m_alpha){
        m_alpha = _alpha;
        setStyleSheet("QLabel{ background: transparent; font-style: italic; color: rgba(170, 0, 0, " + QString::number(_alpha) + "); font-size: 100px;}");
        emit alphaChanged();
    }
}
