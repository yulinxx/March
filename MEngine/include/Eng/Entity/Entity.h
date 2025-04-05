#ifndef ENTITY_H
#define ENTITY_H

#include "MEngineAPI.h"
#include "Ut/tools.h"


// #include <Eigen/Eigen>
#include <string>

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
        UNKNOWN
    };

    class MENGINE_API Entity
    {
    public:
        Entity();
        virtual ~Entity();

    public:
        virtual Ut::Vec2d getValue(double t);
        virtual double EvalParam(const Ut::Vec2& p);

        virtual Ut::Rect2d getRect() const
        {
            return Ut::Rect2d();
        }

    public:
        // const std::string& getName() const;
        //void setName(const std::string& name);

        EntType m_eType;
        size_t m_nId;
        // EigenVector2dWrapper m_basePt;
        Ut::Vec2d m_basePt;
        bool m_bReverse = false;
        bool m_bClosed = false;
    private:
    };
}

#endif // ENTITY_H