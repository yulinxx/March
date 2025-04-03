#include "OptDrawLine.h"

OptDrawLine::OptDrawLine(MEngine::Scene* scene) : OptBase(scene) {}

void OptDrawLine::onMousePress(const QPointF& point) {
    //m_scene->setStartPoint(point);
}

void OptDrawLine::onMouseMove(const QPointF& start, const QPointF& end) {
    //m_scene->updateTempLine(start, end);
}

void OptDrawLine::onMouseRelease(const QPointF& start, const QPointF& end) {
    //m_scene->addLine(start, end);
}