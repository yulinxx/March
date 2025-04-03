#ifndef OPTDRAWLINE_H
#define OPTDRAWLINE_H

#include "Operation/OptBase.h"

class OptDrawLine : public OptBase
{
public:
    OptDrawLine(MEngine::Scene* scene);

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // OPTDRAWLINE_H