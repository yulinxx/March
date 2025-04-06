#ifndef CUBIC_BEZIER_H
#define CUBIC_BEZIER_H

#include "Entity.h"

namespace MEngine
{
    class MENGINE_API CubicBezier : public Entity
    {
    public:
        CubicBezier();
        ~CubicBezier() override;

    public:
        void clear();

        // 设置贝塞尔曲线：通过四个控制点
        void setByControlPoints(const Ut::Vec2& p0, const Ut::Vec2& p1,
            const Ut::Vec2& p2, const Ut::Vec2& p3);
        // 设置采样点数（控制平滑度）
        void setSegments(size_t nSegments);

        // 获取顶点数据，用于绘制
        std::pair<Ut::Vec2*, size_t> getData() const;

        // 获取控制点
        void getControlPoints(Ut::Vec2& p0, Ut::Vec2& p1, Ut::Vec2& p2, Ut::Vec2& p3) const;

        // 获取曲线上的点（参数 t 从 0 到 1）
        Ut::Vec2 evaluate(double t) const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // CUBIC_BEZIER_H

#if 0
int main()
{
    MEngine::CubicBezier bezier;
    bezier.setByControlPoints(
        Ut::Vec2(0.0, 0.0),    // 起点 P0
        Ut::Vec2(1.0, 2.0),    // 控制点 P1
        Ut::Vec2(2.0, 2.0),    // 控制点 P2
        Ut::Vec2(3.0, 0.0)     // 终点 P3
    );
    bezier.setSegments(32);

    renderBezier(bezier);

    // 示例：获取 t=0.5 处的点
    Ut::Vec2 midPoint = bezier.evaluate(0.5);
    std::cout << "Mid point: (" << midPoint.x() << ", " << midPoint.y() << ")\n";

    return 0;
}
#endif