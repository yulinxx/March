#ifndef OPTDRAWELLIPSE_H
#define OPTDRAWELLIPSE_H

#include "Operation/OptBase.h"

class OptDrawEllipse : public OptBase
{
public:
    OptDrawEllipse(MEngine::Scene* scene);
    
public:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    QPointF m_startPoint;
};

#endif // OPTDRAWELLIPSE_H