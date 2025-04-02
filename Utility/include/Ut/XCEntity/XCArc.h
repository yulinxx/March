#ifndef XCARC_H
#define XCARC_H

#include "XCEntity.h"
#include "../UtilityAPI.h"
#include <Eigen/Eigen>

namespace XC
{
    struct UTILITY_API XCArc : public XCEntity
    {
        double m_dRadius;
        double m_dStartAngle;
        double m_dEndAngle;

        virtual Ut::Vec2d value(double t) override;
        virtual double EvalParam(const Ut::Vec2d& p) override;
    };
}

#endif // XCARC_H