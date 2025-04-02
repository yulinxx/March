#include "XCEntity/XCLine.h"
#include <stdexcept>

namespace XC
{
    Ut::Vec2d XCLine::value(double t, bool reverse)
    {
        if (t < 0 || t > 1)
            throw std::runtime_error("Parameter t is out of range [0, 1].");

        if (reverse)
            t = 1 - t;
        // return basePoint + t * (secPoint - basePoint).normalized();
        return Ut::Vec2d(0.0, 0.0);
    }

    double XCLine::EvalParam(const Ut::Vec2d& p)
    {
        Ut::Vec2d& a = basePoint;
        Ut::Vec2d& b = secPoint;
        Ut::Vec2d ab = b - a;
        Ut::Vec2d ap = p - a;
        const double c1 = ap.dot(ab);
        if (c1 <= 0.0)
            return 0; // 距离到点 a

        double c2 = ab.dot(ab);
        if (c2 <= c1)
            return 1; // 距离到点 b

        // 计算垂直距离：|ab × ap| / |ab|
        double t = c1 / c2;
        if (reverse)
            return 1 - t;

        return t;
    }
}