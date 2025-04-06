#include "OptDrawPoint.h"

OptDrawPoint::OptDrawPoint(MEngine::Scene* scene) : OptBase(scene)
{
    m_drawType = DrawType::Point;
}

OptDrawPoint::~OptDrawPoint()
{
}

void OptDrawPoint::enter()
{
}

void OptDrawPoint::exit()
{
}

void OptDrawPoint::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
    }
}

void OptDrawPoint::mouseReleaseEvent(QMouseEvent* event)
{
}

void OptDrawPoint::mouseMoveEvent(QMouseEvent* event)
{
}

void OptDrawPoint::wheelEvent(QWheelEvent* event)
{
}

void OptDrawPoint::keyPressEvent(QKeyEvent* event)
{
}