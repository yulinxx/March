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

        // ���ñ��������ߣ�ͨ���ĸ����Ƶ�
        void setByControlPoints(const Ut::Vec2& p0, const Ut::Vec2& p1,
            const Ut::Vec2& p2, const Ut::Vec2& p3);
        // ���ò�������������ƽ���ȣ�
        void setSegments(size_t nSegments);

        // ��ȡ�������ݣ����ڻ���
        std::pair<Ut::Vec2*, size_t> getData() const;

        // ��ȡ���Ƶ�
        void getControlPoints(Ut::Vec2& p0, Ut::Vec2& p1, Ut::Vec2& p2, Ut::Vec2& p3) const;

        // ��ȡ�����ϵĵ㣨���� t �� 0 �� 1��
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
        Ut::Vec2(0.0, 0.0),    // ��� P0
        Ut::Vec2(1.0, 2.0),    // ���Ƶ� P1
        Ut::Vec2(2.0, 2.0),    // ���Ƶ� P2
        Ut::Vec2(3.0, 0.0)     // �յ� P3
    );
    bezier.setSegments(32);

    renderBezier(bezier);

    // ʾ������ȡ t=0.5 ���ĵ�
    Ut::Vec2 midPoint = bezier.evaluate(0.5);
    std::cout << "Mid point: (" << midPoint.x() << ", " << midPoint.y() << ")\n";

    return 0;
}
#endif