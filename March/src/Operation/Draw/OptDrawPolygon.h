#ifndef OPTDRAWPOLYGON_H
#define OPTDRAWPOLYGON_H

#include "Operation/OptBase.h"

class OptDrawPolygon : public OptBase {
public:
    OptDrawPolygon(MEngine::Scene* scene);
    void onMousePress(const QPointF& point) override;
    void onMouseMove(const QPointF& start, const QPointF& end) override;
    void onMouseRelease(const QPointF& start, const QPointF& end) override;
};

#endif // OPTDRAWPOLYGON_H