#ifndef XCCIRCLE_H
#define XCCIRCLE_H

#include "XCEntity.h"
#include "../UtilityAPI.h"

#include <Eigen/Eigen>

namespace XC
{
    struct UTILITY_API XCCircle : public XCEntity
    {
        double m_dRadius{ 0.0 };

        virtual Ut::Vec2d value(double t);
        virtual double EvalParam(const Ut::Vec2d& p);
        XCCircle();
    };
}

#endif // XCCIRCLE_H