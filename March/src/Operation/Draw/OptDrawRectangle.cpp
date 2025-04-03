#include "OptDrawRectangle.h"

OptDrawRectangle::OptDrawRectangle(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawRectangle::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        //m_scene->setRectTopLeft(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawRectangle::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        //QPointF topLeft = m_scene->getRectTopLeft();
        //QPointF bottomRight = event->pos();
        //m_scene->addRectangle(Ut::Vec2d(topLeft.x(), topLeft.y()), Ut::Vec2d(bottomRight.x(), bottomRight.y()));
    }
}

void OptDrawRectangle::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //QPointF topLeft = m_scene->getRectTopLeft();
        //QPointF bottomRight = event->pos();
        //m_scene->updateTempRectangle(Ut::Vec2d(topLeft.x(), topLeft.y()), Ut::Vec2d(bottomRight.x(), bottomRight.y()));
    }
}

void OptDrawRectangle::wheelEvent(QWheelEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawRectangle::keyPressEvent(QKeyEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}