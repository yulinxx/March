#ifndef OPTDRAWPOINT_H
#define OPTDRAWPOINT_H

#include "Operation/OptBase.h"

class OptDrawPoint : public OptBase
{
public:
    OptDrawPoint(MEngine::Scene* scene);
    ~OptDrawPoint() override;

    // 实现enter()和exit()函数
    void enter() override;
    void exit() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // OPTDRAWPOINT_H