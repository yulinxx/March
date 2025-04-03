#include "OptDrawBezierCurve.h"

OptDrawBezierCurve::OptDrawBezierCurve(MEngine::Scene* scene)
    : OptBase(scene), m_pointCount(0)
{
}

void OptDrawBezierCurve::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_pointCount < 4)
    {
        m_points[m_pointCount++] = event->pos();
        if (m_pointCount == 4)
        {
            // 绘制贝塞尔曲线
            //m_scene->addBezierCurve(m_points);
            m_pointCount = 0;
        }
    }
}

void OptDrawBezierCurve::mouseReleaseEvent(QMouseEvent* event)
{
    // 处理鼠标释放事件
}

void OptDrawBezierCurve::mouseMoveEvent(QMouseEvent* event)
{
    // 处理鼠标移动事件
}

void OptDrawBezierCurve::wheelEvent(QWheelEvent* event)
{
    // 处理鼠标滚轮事件
}

void OptDrawBezierCurve::keyPressEvent(QKeyEvent* event)
{
    // 处理按键事件
}