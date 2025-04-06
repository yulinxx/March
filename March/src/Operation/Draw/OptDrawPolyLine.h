#ifndef OPTDRAWPOLYLINE_H
#define OPTDRAWPOLYLINE_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class PolyLine;
}

class OptDrawPolyLine : public OptBase
{
    using Super = OptBase;

public:
    OptDrawPolyLine(MEngine::Scene* scene);
    ~OptDrawPolyLine() override;

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
    void drawPolyLine();

private:
    bool m_bDrawing = true;             // 是否正在绘制
    bool m_bClosed = false;             // 是否闭合折线
    std::vector<Ut::Vec2d> m_points;    // 已添加的顶点
    Ut::Vec2d m_currentPoint;           // 当前鼠标位置（预览点）

    std::shared_ptr<MEngine::PolyLine> m_polyLinePreview = nullptr;  // 预览折线
};

#endif // OPTDRAWPOLYLINE_H