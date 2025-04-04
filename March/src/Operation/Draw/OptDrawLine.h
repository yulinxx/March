#ifndef OPTDRAWLINE_H
#define OPTDRAWLINE_H

#include "Operation/OptBase.h"

using Super = OptBase;

namespace MEngine
{
    class Line;
}

class OptDrawLine : public OptBase
{
public:
    OptDrawLine(MEngine::Scene* scene);
    ~OptDrawLine() override;


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
    void drawLine();

private:
    size_t m_nPts = 0;
    Ut::Vec2d m_startPoint;
    Ut::Vec2d m_endPoint;


    std::shared_ptr<MEngine::Line> m_linePreview= nullptr;
};

#endif // OPTDRAWLINE_H