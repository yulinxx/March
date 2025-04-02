#include "Entity/Line.h"
#include "Ut/Rect.h"

#include <stdexcept>

namespace MEngine
{
    Line::Line()
    {
        m_eType = ETYPE::LINE;
    }

    Line::Line(Ut::Vec2d& ptS, Ut::Vec2d& ptE)
    {
        m_basePt = ptS;
        m_secPoint = ptE;
    }

    Line::~Line()
    {
    }

    // AABB快速计算（直接取坐标极值） AxisAlignedBoundingBox
    Ut::AxisAlignedBoundingBox Line::CalcAABB()
    {
        return Ut::AxisAlignedBoundingBox(
            Ut::Vec2d(std::min(m_basePt.x(), m_secPoint.x()),
                std::min(m_basePt.y(), m_secPoint.y())),
            Ut::Vec2d(std::max(m_basePt.x(), m_secPoint.x()),
                std::max(m_basePt.y(), m_secPoint.y()))
        );
    }

    // 紧密包围盒（实际就是线段本身） TightBoundingBox
    // Ut::TBB Line::CalcTightBBox()
    // {
    //     return Ut::TBB(m_basePt, m_secPoint);
    // }

// Vec2 Line::getValue(double t, bool m_bReverse)
// {
//     if (t < 0 || t > 1)
//         throw std::runtime_error("t out of range");
//     if (m_bReverse)
//         t = 1 - t;
//     return m_basePt + t * (m_secPoint - m_basePt).normalized();
// }

// double Line::EvalParam(const Vec2 &p)
// {
//     Vec2 &a = m_basePt;
//     Vec2 &b = m_secPoint;
//     Vec2 ab = b - a;
//     Vec2 ap = p - a;
//     const double c1 = ap.dot(ab);
//     if (c1 <= 0.0)
//         return 0;

//     double c2 = ab.dot(ab);
//     if (c2 <= c1)
//         return 1;

//     double t = c1 / c2;
//     if (m_bReverse)
//         return 1 - t;

//     return t;
// }
}