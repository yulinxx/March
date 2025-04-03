#ifndef OPTBASE_H
#define OPTBASE_H

#include <QPointF>

#include "Scene/Scene.h"

class OptBase
{
public:
    OptBase(MEngine::Scene* scene) : m_scene(scene)
    {
    }

    virtual ~OptBase()
    {
    }

public:
    virtual void onMousePress(const QPointF& point) = 0;
    virtual void onMouseMove(const QPointF& start, const QPointF& end) = 0;
    virtual void onMouseRelease(const QPointF& start, const QPointF& end) = 0;

private:
    MEngine::Scene* m_scene = nullptr;
};

#endif // OPTBASE_H