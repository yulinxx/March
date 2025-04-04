#include "OptDrawBezierCurve.h"

OptDrawBezierCurve::OptDrawBezierCurve(MEngine::Scene* scene)
    : OptBase(scene), m_pointCount(0)
{
    m_drawType = DrawType::BezierCurve;
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
}

void OptDrawBezierCurve::mouseMoveEvent(QMouseEvent* event)
{
}

void OptDrawBezierCurve::wheelEvent(QWheelEvent* event)
{
}

void OptDrawBezierCurve::keyPressEvent(QKeyEvent* event)
{
}