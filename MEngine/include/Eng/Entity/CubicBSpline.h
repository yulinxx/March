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
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual void transform(const Ut::Mat3& matrix) override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        // 设置控制点
        void setControlPoints(const std::vector<Ut::Vec2>& points, bool closed = false);
        // 设置采样点数（每段曲线的采样点）
        void setSegmentsPerSpan(size_t nSegments);
        // 设置是否闭合曲线
        void setClosed(bool closed);

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

        spline.setControlPoints(points, false); // 开合曲线
        spline.setSegmentsPerSpan(32);

        renderBSpline(spline);

        // 示例：闭合曲线
        spline.setClosed(true);
        renderBSpline(spline);

        // 示例：获取 t=0.5 处的点
        Ut::Vec2 midPoint = spline.evaluate(0.5);
        std::cout << "Mid point: (" << midPoint.x() << ", " << midPoint.y() << ")\n";

        return 0;
    }
}
#endif