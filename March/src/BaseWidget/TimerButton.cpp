#include "TimerButton.h"
#include <QMouseEvent>

TimerButton::TimerButton(QWidget* parent)
    : QPushButton(parent)
    , m_timer(new QTimer(this))
{
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        setEnabled(true);
        emit sigStateChanged(true);
        });
}

void TimerButton::setDisabledDuration(int milliseconds)
{
    m_duration = milliseconds;
}

void TimerButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        setEnabled(false);
        m_timer->start(m_duration);
        emit sigStateChanged(false);
    }

    QPushButton::mousePressEvent(event);
}