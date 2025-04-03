#include "OptDrawLine.h"

OptDrawLine::OptDrawLine(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawLine::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        //m_scene->setStartPoint(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawLine::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        //QPointF start = m_scene->getStartPoint();
        //QPointF end = event->pos();
        //m_scene->addLine(Ut::Vec2d(start.x(), start.y()), Ut::Vec2d(end.x(), end.y()));
    }
}

void OptDrawLine::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //QPointF start = m_scene->getStartPoint();
        //QPointF end = event->pos();
        //m_scene->updateTempLine(Ut::Vec2d(start.x(), start.y()), Ut::Vec2d(end.x(), end.y()));
    }
}

void OptDrawLine::wheelEvent(QWheelEvent* event)
{
}

void OptDrawLine::keyPressEvent(QKeyEvent* event)
{
}