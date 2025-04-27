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
    bool m_bDrawing = false;  // �Ƿ����ڻ���
    std::vector<Ut::Vec2d> m_controlPoints;  // ���Ƶ��б���� 4 ����
    Ut::Vec2d m_currentPoint;                // ��ǰ���λ�ã�Ԥ���㣩

    std::shared_ptr<MEngine::CubicBezier> m_bezierPreview = nullptr;  // Ԥ������������
};

#endif // OPTDRAWCUBICBEZIER_H