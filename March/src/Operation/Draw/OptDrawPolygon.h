#ifndef OPTDRAWPOLYGON_H
#define OPTDRAWPOLYGON_H

#include "Operation/OptBase.h"

class OptDrawPolygon : public OptBase 
{
public:
    OptDrawPolygon(MEngine::Scene* scene);

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // OPTDRAWPOLYGON_H