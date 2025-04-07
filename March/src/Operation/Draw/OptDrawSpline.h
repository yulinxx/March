#ifndef OPTDRAWSPLINE_H
#define OPTDRAWSPLINE_H

#include "Operation/OptBase.h"
#include <memory>

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
    bool m_isDrawing = false;         // 是否正在绘制
    bool m_isDragging = false;        // 是否正在拖动控制点
    bool m_isClosed = false;          // 是否闭合曲线
    int m_selectedPointIndex = -1;    // 当前选中的控制点索引（拖动时使用）

    std::vector<Ut::Vec2d> m_controlPoints;  // 控制点列表
    Ut::Vec2d m_currentMousePos;             // 当前鼠标位置（用于预览或拖动）

    std::shared_ptr<MEngine::CubicBSpline> m_splinePreview;  // 预览样条曲线
    constexpr static double DRAG_THRESHOLD = 10.0;           // 拖动控制点的距离阈值
};

#endif // OPTDRAWSPLINE_H