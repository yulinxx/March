#include "OptDrawCircle.h"

OptDrawCircle::OptDrawCircle(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawCircle::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        // m_scene->setCenterPoint(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawCircle::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // QPointF center = m_scene->getCenterPoint();
        // QPointF edge = event->pos();
        // m_scene->addCircle(Ut::Vec2d(center.x(), center.y()), Ut::Vec2d(edge.x(), edge.y()));
    }
}

void OptDrawCircle::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // QPointF center = m_scene->getCenterPoint();
        // QPointF edge = event->pos();
        // m_scene->updateTempCircle(Ut::Vec2d(center.x(), center.y()), Ut::Vec2d(edge.x(), edge.y()));
    }
}

void OptDrawCircle::wheelEvent(QWheelEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawCircle::keyPressEvent(QKeyEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}