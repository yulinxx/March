#ifndef POINT_H
#define POINT_H

#include "Entity.h"

namespace MEngine
{
    class MENGINE_API Point : public Entity
    {
    public:
        Point();
        Point(Ut::Vec2d pos);

        template<typename T>
        Point(T x, T y) : m_vPos(double(x), double(y))
        {
        }

        ~Point() override;

    public:
        virtual Ut::Rect2d getRect() const override;

    private:
        Ut::Vec2d m_vPos;
    };
}

#endif // POINT_H