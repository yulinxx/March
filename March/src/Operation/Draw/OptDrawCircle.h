#ifndef OPTDRAWCIRCLE_H
#define OPTDRAWCIRCLE_H

#include "Operation/OptBase.h"

class OptDrawCircle : public OptBase {
public:
    OptDrawCircle(MEngine::Scene* scene);
    void onMousePress(const QPointF& point) override;
    void onMouseMove(const QPointF& start, const QPointF& end) override;
    void onMouseRelease(const QPointF& start, const QPointF& end) override;
};

#endif // OPTDRAWCIRCLE_H