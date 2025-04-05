#ifndef OPTDRAWPOLYGON_H
#define OPTDRAWPOLYGON_H

#include "Operation/OptBase.h"

namespace MEngine
{
    class Polygon;
}

class OptDrawPolygon : public OptBase
{
    using Super = OptBase;

public:
    OptDrawPolygon(MEngine::Scene* scene);

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
    void setPolygonData(MEngine::Polygon* polygon);
    void drawPolygon();

private:
    bool m_bFirst= true;

    Ut::Vec2d m_startPoint;
    Ut::Vec2d m_endPoint;

    std::shared_ptr<MEngine::Polygon> m_polygonPreview = nullptr;

};

#endif // OPTDRAWPOLYGON_H