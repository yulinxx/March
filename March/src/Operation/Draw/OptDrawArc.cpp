#include "OptDrawArc.h"

OptDrawArc::OptDrawArc(MEngine::Scene* scene) : OptBase(scene)
{
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
    // 可根据需要添加自定义处理逻辑
}

void OptDrawArc::keyPressEvent(QKeyEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}