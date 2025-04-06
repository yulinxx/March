#ifndef OPTDRAWSPLINE_H
#define OPTDRAWSPLINE_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class CubicBSpline;
}

class OptDrawSpline : public OptBase
{
    using Super = OptBase;

public:
    OptDrawSpline(MEngine::Scene* scene);
    ~OptDrawSpline() override;

public:
    void enter() override;
    void exit() override;

public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void setSplineData(MEngine::CubicBSpline* spline);
    void drawSpline();
    void updatePreview();

private:
    bool m_bDrawing = false;  // 是否正在绘制
    bool m_bClosed = false;   // 是否闭合曲线

    std::vector<Ut::Vec2d> m_controlPoints;  // 控制点列表
    Ut::Vec2d m_currentPoint;                // 当前鼠标位置（最后一个控制点预览）

    std::shared_ptr<MEngine::CubicBSpline> m_splinePreview = nullptr;  // 预览样条曲线
};

#endif // OPTDRAWSPLINE_H