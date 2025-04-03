#ifndef OPTDRAWSPLINE_H
#define OPTDRAWSPLINE_H

#include "Operation/OptBase.h"

class OptDrawSpline : public OptBase
{
public:
    OptDrawSpline(MEngine::Scene* scene);
    ~OptDrawSpline() override;

    // 实现enter()和exit()函数
    void enter() override;
    void exit() override;

public:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);
};

#endif // OPTDRAWSPLINE_H