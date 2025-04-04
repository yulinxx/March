#include "OptDrawArc.h"

OptDrawArc::OptDrawArc(MEngine::Scene* scene) : OptBase(scene)
{
    m_drawType = DrawType::Arc;
}

void OptDrawArc::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        // m_scene->setArcStartPoint(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawArc::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // QPointF start = m_scene->getArcStartPoint();
        // QPointF end = event->pos();
        // m_scene->addArc(Ut::Vec2d(start.x(), start.y()), Ut::Vec2d(end.x(), end.y()));
    }
}

void OptDrawArc::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // QPointF start = m_scene->getArcStartPoint();
        // QPointF end = event->pos();
        // m_scene->updateTempArc(Ut::Vec2d(start.x(), start.y()), Ut::Vec2d(end.x(), end.y()));
    }
}

void OptDrawArc::wheelEvent(QWheelEvent* event)
{
    
}

void OptDrawArc::keyPressEvent(QKeyEvent* event)
{
    
}