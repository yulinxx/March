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

        // ���ÿ��Ƶ�
        void setControlPoints(const std::vector<Ut::Vec2>& points, bool closed = false);
        // ���ò���������ÿ�����ߵĲ����㣩
        void setSegmentsPerSpan(size_t nSegments);
        // �����Ƿ�պ�����
        void setClosed(bool closed);

        // ��ȡ�������ݣ����ڻ���
        std::pair<Ut::Vec2*, size_t> getData() const;

        // ��ȡ���Ƶ�
        std::vector<Ut::Vec2> getControlPoints() const;

        // ��ȡ�����ϵĵ㣨���� t �� 0 �� 1��
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