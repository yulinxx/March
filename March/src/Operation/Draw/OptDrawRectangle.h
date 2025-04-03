#ifndef OPTDRAWRECTANGLE_H
#define OPTDRAWRECTANGLE_H

#include "Operation/OptBase.h"

class OptDrawRectangle : public OptBase
{
public:
    OptDrawRectangle(MEngine::Scene* scene);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // OPTDRAWRECTANGLE_H