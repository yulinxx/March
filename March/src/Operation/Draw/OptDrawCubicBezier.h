#ifndef OPTDRAWCUBICBEZIER_H
#define OPTDRAWCUBICBEZIER_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class CubicBezier;
}

class OptDrawCubicBezier : public OptBase
{

public:
    OptDrawCubicBezier(MEngine::Scene* scene);
    ~OptDrawCubicBezier() override;

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
    void setBezierData(MEngine::CubicBezier* bezier);
    void drawBezier();
    void updatePreview();

private:
    bool m_bDrawing = false;  // 是否正在绘制
    std::vector<Ut::Vec2d> m_controlPoints;  // 控制点列表（最多 4 个）
    Ut::Vec2d m_currentPoint;                // 当前鼠标位置（预览点）

    std::shared_ptr<MEngine::CubicBezier> m_bezierPreview = nullptr;  // 预览贝塞尔曲线
};

#endif // OPTDRAWCUBICBEZIER_H