#include "XCEntity/XCCircle.h"
#include <stdexcept>
#include <cmath>

namespace XC
{
    Ut::Vec2d XCCircle::value(double t)
    {
        if (t < 0 || t > 1)
            throw std::runtime_error("Parameter t is out of range [0, 1].");

        if (reverse)
            t = 1 - t;

        return Ut::Vec2d(basePoint.x() + m_dRadius * cos(t * 2 * M_PI),
            basePoint.y() + m_dRadius * sin(t * 2 * M_PI));
    }

    double XCCircle::EvalParam(const Ut::Vec2d& p)
    {
        double t = 0.0;
        // auto v = (p - basePoint);
        // t = atan2(v.y, v.x) / (2 * M_PI);
        // if (reverse)
        //     return 1 - t;
        return t;
    }

    XCCircle::XCCircle()
    {
        isClosed = true;
    }
}