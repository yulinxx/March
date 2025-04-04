#include "OptDrawEllipse.h"

OptDrawEllipse::OptDrawEllipse(MEngine::Scene* scene) : OptBase(scene)
{
    m_drawType = DrawType::Ellipse;
}

void OptDrawEllipse::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_startPoint = event->pos();
    }
}

void OptDrawEllipse::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF endPoint = event->pos();
    }
}

void OptDrawEllipse::mouseMoveEvent(QMouseEvent* event)
{
}

void OptDrawEllipse::wheelEvent(QWheelEvent* event)
{
}

void OptDrawEllipse::keyPressEvent(QKeyEvent* event)
{
}