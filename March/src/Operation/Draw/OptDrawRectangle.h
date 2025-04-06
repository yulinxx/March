#ifndef OPTDRAWRECTANGLE_H
#define OPTDRAWRECTANGLE_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class Rectangle;
}

class OptDrawRectangle : public OptBase
{
    using Super = OptBase;

public:
    OptDrawRectangle(MEngine::Scene* scene);

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
    void setRectangleData(MEngine::Rectangle* rectangle);
    void drawRectange();

private:
    bool m_bFirst = true;

    Ut::Vec2d m_startPoint;
    Ut::Vec2d m_endPoint;

    std::shared_ptr<MEngine::Rectangle> m_rectPreview = nullptr;
};

#endif // OPTDRAWRECTANGLE_H