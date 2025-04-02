#ifndef POLYLINE_H
#define POLYLINE_H

#include "Entity.h"
#include <memory>
#include <vector>

namespace MEngine
{
    class MENGINE_API PolyLine : public Entity
    {
    public:
        // std::vector<std::unique_ptr<Entity>> entitylist;

        PolyLine();
        ~PolyLine() override;

        // Vec2 getValue(double t) override;
        // double EvalParam(const Vec2& p) override;
    };
}

#endif  // POLYLINE_H