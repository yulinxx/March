#ifndef OPTDRAWARC_H
#define OPTDRAWARC_H

#include "Operation/OptBase.h"

class OptDrawArc : public OptBase {
public:
    OptDrawArc(MEngine::Scene* scene);
    void onMousePress(const QPointF& point) override;
    void onMouseMove(const QPointF& start, const QPointF& end) override;
    void onMouseRelease(const QPointF& start, const QPointF& end) override;
};

#endif // OPTDRAWARC_H