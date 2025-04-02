#ifndef LINE_H
#define LINE_H

#include "Entity.h"
#include "Ut/Rect.h"

namespace MEngine
{
    class MENGINE_API Line : public Entity
    {
    public:
        Line();
        Line(Ut::Vec2d& ptS, Ut::Vec2d& ptE);
        ~Line();

    public:
        Ut::AxisAlignedBoundingBox CalcAABB();
        // Ut::TBB CalcTightBBox();

        // public:
        //     // Vec2 getValue(double t, bool m_bReverse = false) override;
        //     // double EvalParam(const Vec2 &p) override;

    private:
    public:
        Ut::Vec2d m_secPoint;
    };
}

#endif // LINE_H