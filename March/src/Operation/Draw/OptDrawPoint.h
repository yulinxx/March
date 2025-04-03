#ifndef OPTDRAWPOINT_H
#define OPTDRAWPOINT_H

#include "Operation/OptBase.h"

class OptDrawPoint : public OptBase
{
public:
    OptDrawPoint(MEngine::Scene *scene);

public:
    void onMousePress(const QPointF &point) override;
    void onMouseMove(const QPointF &start, const QPointF &end) override;
    void onMouseRelease(const QPointF &start, const QPointF &end) override;
};

#endif // OPTDRAWPOINT_H