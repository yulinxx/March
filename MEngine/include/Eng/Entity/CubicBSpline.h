#ifndef CUBIC_BSPLINE_H
#define CUBIC_BSPLINE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API CubicBSpline : public Entity
    {
    public:
        CubicBSpline();
        ~CubicBSpline() override;

    public:
        void clear();

        // 设置控制点
        void setControlPoints(const std::vector<Ut::Vec2>& points, bool closed = false);
        // 设置采样点数（每段曲线的采样点）
        void setSegmentsPerSpan(size_t nSegments);
        // 设置是否闭合曲线
        void setClosed(bool closed);

        // 获取顶点数据，用于绘制

        virtual std::pair<Ut::Vec2*, size_t> getData() const;
        //std::pair<Ut::Vec2*, size_t> getData() const;
        //virtual Ut::Rect2d& getRect();

        // 获取控制点
        std::vector<Ut::Vec2> getControlPoints() const;

        // 获取曲线上的点（参数 t 从 0 到 1）
        Ut::Vec2 evaluate(double t) const;

    private:
        void updateVertices();
        void computeKnots();
        double basisFunction(int i, int k, double t, const std::vector<double>& knots) const;

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // CUBIC_BSPLINE_H

#if 0
{
    int main()
    {
        MEngine::CubicBSpline spline;
        std::vector<Ut::Vec2> points = {
            Ut::Vec2(0.0, 0.0),
            Ut::Vec2(1.0, 2.0),
            Ut::Vec2(2.0, 2.0),
            Ut::Vec2(3.0, 0.0),
            Ut::Vec2(4.0, -1.0)
        };
        spline.setControlPoints(points, false); // ��������
        spline.setSegmentsPerSpan(32);

        renderBSpline(spline);

        // ʾ�����պ�����
        spline.setClosed(true);
        renderBSpline(spline);

        // ʾ������ȡ t=0.5 ���ĵ�
        Ut::Vec2 midPoint = spline.evaluate(0.5);
        std::cout << "Mid point: (" << midPoint.x() << ", " << midPoint.y() << ")\n";

        return 0;
    }
}
#endif