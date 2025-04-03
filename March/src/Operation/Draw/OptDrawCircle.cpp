#include "OptDrawCircle.h"

OptDrawCircle::OptDrawCircle(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawCircle::onMousePress(const QPointF& point)
{
    //m_scene->setCenterPoint(point);
}

void OptDrawCircle::onMouseMove(const QPointF& start, const QPointF& end)
{
    //m_scene->updateTempCircle(start, end);
}

void OptDrawCircle::onMouseRelease(const QPointF& start, const QPointF& end)
{
    //m_scene->addCircle(start, end);
}