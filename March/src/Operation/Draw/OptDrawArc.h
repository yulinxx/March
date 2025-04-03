#ifndef OPTDRAWARC_H
#define OPTDRAWARC_H

#include "Operation/OptBase.h"

class OptDrawArc : public OptBase
{
public:
    OptDrawArc(MEngine::Scene* scene);

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // OPTDRAWARC_H