#include "Entity/Arc.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    Arc::Arc()
    {
        m_eType = EntType::ARC;
    }
    Arc::~Arc()
    {
    }

    Ut::Vec2d Arc::getValue(double t)
    {
        if (t < 0 || t > 1)
            throw std::runtime_error("t out of range");
        if (m_bReverse)
            t = 1 - t;
        double ang = m_dStartAngle + t * (m_dEndAngle - m_dStartAngle);
        return Ut::Vec2d(m_basePt.x() + m_dRadius * std::cos(ang), m_basePt.y() + m_dRadius * std::sin(ang));
    }

    double Arc::EvalParam(const Ut::Vec2d& p)
    {
        double t;
        auto v = (p - m_basePt);
        double ang = std::atan2(v.y(), v.x());

        if (ang >= m_dStartAngle && ang <= m_dEndAngle)
        {
            t = (ang - m_dStartAngle) / (m_dEndAngle - m_dStartAngle);
        }
        // else if ((getValue(0) - p).squaredNorm() < (getValue(1) - p).squaredNorm())
        // {
        //     t = 0;
        // }
        else
        {
            t = 1;
        }
        if (m_bReverse)
        {
            return 1 - t;
        }
        return t;
    }
}