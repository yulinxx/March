#include "XCEntity/XCArc.h"
#include <cmath>
#include <stdexcept>

namespace XC
{
    // 计算圆弧上参数 t 对应的点
    Ut::Vec2d XCArc::value(double t)
    {
        if (t < 0 || t > 1)
        {
            throw std::invalid_argument("Parameter t must be in the range [0, 1].");
        }
        if (reverse)
        {
            t = 1 - t;
        }
        double ang = m_dStartAngle + t * (m_dEndAngle - m_dStartAngle);
        // 计算点的坐标
        return Ut::Vec2d(basePoint.x() + m_dRadius * std::cos(ang), basePoint.y() + m_dRadius * std::sin(ang));
    }

    // 根据点 p 计算对应的参数 t
    double XCArc::EvalParam(const Ut::Vec2d& p)
    {
        double t = 0.0;
        // auto v = (p - basePoint);
        // double ang = std::atan2(v.y, v.x);

        // if (ang >= m_dStartAngle && ang <= m_dEndAngle) {
        //     t = (ang - m_dStartAngle) / (m_dEndAngle - m_dStartAngle);
        // } else if ((value(0) - p).squaredNorm() < (value(1) - p).squaredNorm()) {
        //     t = 0;
        // } else {
        //     t = 1.0;
        // }
        // if (reverse) {
        //     return 1 - t;
        // }
        return t;
    }
}