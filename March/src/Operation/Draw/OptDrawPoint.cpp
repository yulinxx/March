#include "OptDrawPoint.h"

OptDrawPoint::OptDrawPoint(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawPoint::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        //m_scene->addPoint(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawPoint::mouseReleaseEvent(QMouseEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawPoint::mouseMoveEvent(QMouseEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawPoint::wheelEvent(QWheelEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawPoint::keyPressEvent(QKeyEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}