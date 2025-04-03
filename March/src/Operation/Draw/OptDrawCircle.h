#ifndef OPTDRAWCIRCLE_H
#define OPTDRAWCIRCLE_H

#include "Operation/OptBase.h"

class OptDrawCircle : public OptBase
{
public:
    OptDrawCircle(MEngine::Scene* scene);
    ~OptDrawCircle() override;

    // 实现enter()和exit()函数
    void enter() override;
    void exit() override;

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // OPTDRAWCIRCLE_H