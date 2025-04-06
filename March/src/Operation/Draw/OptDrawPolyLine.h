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
    bool m_bDrawing = true;             // �Ƿ����ڻ���
    bool m_bClosed = false;             // �Ƿ�պ�����
    std::vector<Ut::Vec2d> m_points;    // ����ӵĶ���
    Ut::Vec2d m_currentPoint;           // ��ǰ���λ�ã�Ԥ���㣩

    std::shared_ptr<MEngine::PolyLine> m_polyLinePreview = nullptr;  // Ԥ������
};

#endif // OPTDRAWPOLYLINE_H