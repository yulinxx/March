#ifndef OPTDRAWBEZIERCURVE_H
#define OPTDRAWBEZIERCURVE_H

#include "Operation/OptBase.h"

class OptDrawBezierCurve : public OptBase
{
public:
    OptDrawBezierCurve(MEngine::Scene* scene);

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    int m_pointCount;
    QPointF m_points[4];
};

#endif // OPTDRAWBEZIERCURVE_H