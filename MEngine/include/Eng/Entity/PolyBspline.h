#ifndef POLYBSPLINE_H
#define POLYBSPLINE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API PolyBspline : public Entity
    {
    public:
        PolyBspline();
        ~PolyBspline() override;

    public:
        std::pair<float*, size_t> getLinesData() const;

        int degree;
        // std::vector<double> knots;
        // std::vector<double> weights;
        // std::vector<Vec2> controlPts;
    };
}

#endif  // POLYBSPLINE_H    