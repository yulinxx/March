#include "OptDrawRectangle.h"

OptDrawRectangle::OptDrawRectangle(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawRectangle::onMousePress(const QPointF& point)
{
    //m_scene->setRectTopLeft(point);
}

void OptDrawRectangle::onMouseMove(const QPointF& start, const QPointF& end)
{
    //m_scene->updateTempRectangle(start, end);
}

void OptDrawRectangle::onMouseRelease(const QPointF& start, const QPointF& end)
{
    //m_scene->addRectangle(start, end);
}