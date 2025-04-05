#include "Entity/Circle.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    Circle::Circle()
    {
        m_eType = EntType::CIRCLE;
        m_bClosed = true;
    }
    Circle::~Circle()
    {
    }

    // Vec2 Circle::getValue(double t)
    // {
    //     if (t < 0 || t > 1)
    //         throw std::runtime_error("t out of range");
    //     if (m_bReverse)
    //         t = 1 - t;

    //     return Vec2(m_basePt.x() + Radius * std::cos(t * 2 * M_PI), m_basePt.y() + Radius * std::sin(t * 2 * M_PI));
    // }

    // double Circle::EvalParam(const Vec2 &p)
    // {
    //     auto v = (p - m_basePt);
    //     double t = std::atan2(v.y(), v.x()) / (2 * M_PI);
    //     if (m_bReverse)
    //         return 1 - t;
    //     return t;
    // }
}