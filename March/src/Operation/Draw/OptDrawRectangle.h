#ifndef OPTDRAWRECTANGLE_H
#define OPTDRAWRECTANGLE_H

#include "Operation/OptBase.h"

class OptDrawRectangle : public OptBase
{
public:
    OptDrawRectangle(MEngine::Scene* scene);
    void onMousePress(const QPointF& point) override;
    void onMouseMove(const QPointF& start, const QPointF& end) override;
    void onMouseRelease(const QPointF& start, const QPointF& end) override;
};

#endif // OPTDRAWRECTANGLE_H