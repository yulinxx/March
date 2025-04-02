#include "ResetSlider.h"

ResetSlider::ResetSlider(Qt::Orientation orientation, QWidget* parent)
    : QSlider(orientation, parent)
{
    setDefaultValue(0);
}

int ResetSlider::defaultValue() const
{
    return m_nDefaultValue;
}

void ResetSlider::setDefaultValue(int value)
{
    m_nDefaultValue = qBound(minimum(), value, maximum());
}

void ResetSlider::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        setValue(m_nDefaultValue);
        emit resetValue(m_nDefaultValue);
    }

    QSlider::mouseDoubleClickEvent(event);
}