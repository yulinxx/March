#ifndef OPTDRAWARC_H
#define OPTDRAWARC_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class Arc;
}

class OptDrawArc : public OptBase
{
    using Super = OptBase;

public:
    OptDrawArc(MEngine::Scene* scene);
    ~OptDrawArc() override;

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
    void drawArc();
    void updatePreview();

private:
    size_t m_nPts = 0;            // 当前点的数量（0-3）
    Ut::Vec2d m_startPoint;       // 起点
    Ut::Vec2d m_midPoint;         // 中间点
    Ut::Vec2d m_endPoint;         // 终点（鼠标移动时的预览点）

    std::shared_ptr<MEngine::Arc> m_arcPreview = nullptr;  // 预览圆弧
};

#endif // OPTDRAWARC_H