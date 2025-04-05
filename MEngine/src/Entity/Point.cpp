#include "Entity/Point.h"

namespace MEngine
{
    Point::Point()
    {
        m_eType = EntType::POINT;
    }

    Point::Point(Ut::Vec2d pos)
    {
        m_eType = EntType::POINT;
        m_vPos = pos;
    }

    Point::~Point()
    {
    }

    Ut::Rect2d Point::getRect() const
    {
        return Ut::Rect2d(m_vPos, m_vPos);
    }
}