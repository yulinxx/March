#ifndef OPTDRAWCIRCLE_H
#define OPTDRAWCIRCLE_H

#include "Operation/OptBase.h"

class OptDrawCircle : public OptBase
{
public:
    OptDrawCircle(MEngine::Scene* scene);

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // OPTDRAWCIRCLE_H