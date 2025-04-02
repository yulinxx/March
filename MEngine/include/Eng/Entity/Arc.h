#ifndef ARC_H
#define ARC_H

#include "Entity.h"

namespace MEngine
{
    class MENGINE_API Arc : public Entity
    {
    public:
        Arc();
        ~Arc() override;

    public:
        Ut::Vec2d getValue(double t) override;
        double EvalParam(const Ut::Vec2d& p) override;

    private:
        double m_dRadius = 0.0;
        double m_dStartAngle = 0.0;
        double m_dEndAngle = 0.0;
    };
}

#endif  // ARC_H