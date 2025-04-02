#ifndef XCLINE_H
#define XCLINE_H

#include "XCEntity.h"
#include "../UtilityAPI.h"

#include <Eigen/Eigen>

namespace XC
{
    struct UTILITY_API XCLine : public XCEntity
    {
        virtual Ut::Vec2d value(double t, bool reverse = false);
        virtual double EvalParam(const Ut::Vec2d& p);

        Ut::Vec2d secPoint;
    };
}

#endif // XCLINE_H