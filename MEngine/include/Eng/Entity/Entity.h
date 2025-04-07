#ifndef ENTITY_H
#define ENTITY_H

#include "MEngineAPI.h"
#include "Ut/tools.h"
#include "Ut/Vec.h"
#include "Ut/Rect.h"

namespace MEngine
{
    enum class EntType
    {
        POINT,
        LINE,
        ARC,
        CIRCLE,
        LWPOLYLINE,
        SPLINE,
        POLYGON,
        TEXT,
        ELLIPSE,
        RECTANGLE,
        BSPLINE,
        BEZIER,
        UNKNOWN
    };

    class MENGINE_API Entity
    {
    public:
        Entity();
        virtual ~Entity();

    public:
        virtual double EvalParam(const Ut::Vec2& p);

        virtual std::pair<Ut::Vec2*, size_t> getData() const = 0;

        virtual Ut::Rect2d& getRect();
        void setRect(Ut::Rect2d& rect);

    public:
        Ut::Vec2d getValue(double t);
        // 获取和设置属性
        EntType getType() const;
        size_t getId() const;
        Ut::Vec2d& getBasePoint() const;
        bool isReversed() const;
        bool isClosed() const;

        void setType(EntType type);
        void setId(size_t id);
        void setBasePoint(const Ut::Vec2d& basePt);
        void setReversed(bool reverse);
        void setClosed(bool closed);



    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // ENTITY_H