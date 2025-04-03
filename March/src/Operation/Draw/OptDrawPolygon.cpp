#include "OptDrawPolygon.h"

OptDrawPolygon::OptDrawPolygon(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawPolygon::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        //m_scene->addPolygonVertex(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawPolygon::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        //m_scene->completePolygon();
    }
}

void OptDrawPolygon::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPointF pos = event->pos();
        //m_scene->updateTempPolygon(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawPolygon::wheelEvent(QWheelEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawPolygon::keyPressEvent(QKeyEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}