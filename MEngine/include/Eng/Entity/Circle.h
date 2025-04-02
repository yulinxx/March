#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"

namespace MEngine
{
    class MENGINE_API Circle : public Entity
    {
    public:
        Circle();
        ~Circle() override;

    public:
        // Vec2 getValue(double t) override;
        // double EvalParam(const Vec2 &p) override;

    public:
        double Radius = 0.0;
    };
}

#endif // CIRCLE_H