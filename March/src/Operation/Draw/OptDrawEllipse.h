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
    bool m_bFirst = true;  // �Ƿ��һ�ε��

    Ut::Vec2d m_centerPoint;  // ��Բ����
    Ut::Vec2d m_endPoint;     // ����ƶ�ʱ�Ķ˵㣬���ڼ����᳤

    std::shared_ptr<MEngine::Ellipse> m_ellipsePreview = nullptr;  // Ԥ����Բ
};

#endif // OPTDRAWELLIPSE_H