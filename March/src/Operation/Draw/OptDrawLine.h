#ifndef OPTDRAWLINE_H
#define OPTDRAWLINE_H

#include "Operation/OptBase.h"

using Super = OptBase;

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
    
    void drawLine(); // 绘制直线
private:
    size_t m_nPts = 0;
    Ut::Vec2d m_startPoint;
    Ut::Vec2d m_endPoint;

};

#endif // OPTDRAWLINE_H