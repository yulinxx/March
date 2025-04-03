#include "OptDrawPoint.h"

OptDrawPoint::OptDrawPoint(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawPoint::onMousePress(const QPointF& point)
{
    //m_scene->addPoint(point);
}

void OptDrawPoint::onMouseMove(const QPointF& start, const QPointF& end)
{
    // 点绘制不需要处理鼠标移动
}

void OptDrawPoint::onMouseRelease(const QPointF& start, const QPointF& end)
{
    // 点绘制不需要处理鼠标释放
}