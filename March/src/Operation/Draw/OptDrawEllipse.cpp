#include "OptDrawEllipse.h"

OptDrawEllipse::OptDrawEllipse(MEngine::Scene* scene) : OptBase(scene)
{
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
        // 绘制椭圆
        //m_scene->addEllipse(m_startPoint, endPoint);
    }
}

void OptDrawEllipse::mouseMoveEvent(QMouseEvent* event)
{
    // 处理鼠标移动事件
}

void OptDrawEllipse::wheelEvent(QWheelEvent* event)
{
    // 处理鼠标滚轮事件
}

void OptDrawEllipse::keyPressEvent(QKeyEvent* event)
{
    // 处理按键事件
}