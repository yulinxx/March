#include "OptDrawArc.h"

OptDrawArc::OptDrawArc(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawArc::onMousePress(const QPointF& point)
{
    //m_scene->setArcStartPoint(point);
}

void OptDrawArc::onMouseMove(const QPointF& start, const QPointF& end)
{
    //m_scene->updateTempArc(start, end);
}

void OptDrawArc::onMouseRelease(const QPointF& start, const QPointF& end)
{
    //m_scene->addArc(start, end);
}