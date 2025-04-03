#ifndef OPTDRAWLINE_H
#define OPTDRAWLINE_H

#include "Operation/OptBase.h"

class OptDrawLine : public OptBase {
public:
    OptDrawLine(MEngine::Scene* scene);
    void onMousePress(const QPointF& point) override;
    void onMouseMove(const QPointF& start, const QPointF& end) override;
    void onMouseRelease(const QPointF& start, const QPointF& end) override;
};

#endif // OPTDRAWLINE_H