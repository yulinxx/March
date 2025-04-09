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

    // 定义标志位的枚举
    enum EntFlag{
        Select = 0, // 选择标志位
        Show = 1,   // 显示标志位
        Lock = 2,     // 锁定标志位
        Dirty = 3,    // 脏标记标志位
    };

    class MENGINE_API Entity
    {
    public:
        Entity();
        virtual ~Entity();

    public:
        virtual Ut::Vec2d getValue(double t);
        virtual double EvalParam(const Ut::Vec2& p);

        virtual std::pair<Ut::Vec2*, size_t> getData() const = 0;

        virtual Ut::Rect2d& getRect();
        virtual void clear() = 0;

    public:
        void setRect(Ut::Rect2d& rect);

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

        void setFlag(EntFlag flag, bool b = true);
        bool getFlag(EntFlag flag) const;

    private:
        struct Impl;
        Impl* m_impl = nullptr;
    };
}

#endif // ENTITY_H