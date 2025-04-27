#ifndef OPTDRAWELLIPSE_H
#define OPTDRAWELLIPSE_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class Ellipse;
}

class OptDrawEllipse : public OptBase
{
public:
    OptDrawEllipse(MEngine::Scene* scene);
    ~OptDrawEllipse() override;

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
    void setEllipseData(MEngine::Ellipse* ellipse);
    void drawEllipse();

private:
    bool m_bFirst = true;  // 是否第一次点击

    Ut::Vec2d m_centerPoint;  // 椭圆中心
    Ut::Vec2d m_endPoint;     // 鼠标移动时的端点，用于计算轴长

    std::shared_ptr<MEngine::Ellipse> m_ellipsePreview = nullptr;  // 预览椭圆
};

#endif // OPTDRAWELLIPSE_H