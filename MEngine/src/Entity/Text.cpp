#include "Entity/Text.h"

namespace MEngine
{
    Text::Text()
    {
        setType(EntType::TEXT);
    }

    Text::~Text()
    {
    }

    void Text::clear()
    {
    }

    double Text::getLength() const
    {
        return 0.0;
    }

    Ut::Vec2d Text::getValue(double t)
    {
        return getBasePoint();
    }

    double Text::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}