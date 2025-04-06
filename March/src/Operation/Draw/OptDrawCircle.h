#ifndef OPTDRAWCIRCLE_H
#define OPTDRAWCIRCLE_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class Circle;
}

class OptDrawCircle : public OptBase
{
    using Super = OptBase;

public:
    OptDrawCircle(MEngine::Scene* scene);
    ~OptDrawCircle() override;

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
    void setCircleData(MEngine::Circle* circle);
    void drawCircle();

private:
    bool m_bFirst = true;

    Ut::Vec2d m_startPoint;
    Ut::Vec2d m_endPoint;

    std::shared_ptr<MEngine::Circle> m_circlePreview = nullptr;

};

#endif // OPTDRAWCIRCLE_H