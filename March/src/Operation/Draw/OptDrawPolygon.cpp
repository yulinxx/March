#include "OptDrawPolygon.h"

OptDrawPolygon::OptDrawPolygon(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawPolygon::onMousePress(const QPointF& point)
{
    //m_scene->addPolygonVertex(point);
}

void OptDrawPolygon::onMouseMove(const QPointF& start, const QPointF& end)
{
    //m_scene->updateTempPolygon(end);
}

void OptDrawPolygon::onMouseRelease(const QPointF& start, const QPointF& end)
{
    //m_scene->completePolygon();
}