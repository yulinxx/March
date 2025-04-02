#ifndef XCPOLYLINE_H
#define XCPOLYLINE_H

#include "XCEntity.h"
#include "../UtilityAPI.h"
#include <vector>
#include <memory>

namespace XC
{
    struct UTILITY_API XCPolyLine : public XCEntity
    {
    public:
        XCPolyLine() = default;
        XCPolyLine(const XCPolyLine& other);
        XCPolyLine(XCPolyLine&& other) noexcept = default;
        XCPolyLine& operator=(const XCPolyLine& other);
        XCPolyLine& operator=(XCPolyLine&& other) noexcept = default;
        virtual ~XCPolyLine() = default;

    public:
        void addEntity(XCEntity* entity);

        size_t getEntityCount() const;

        XCEntity* getEntity(size_t index) const;

        virtual Ut::Vec2d value(double t) override;
        virtual double EvalParam(const Ut::Vec2d& p) override;

    private:
        std::vector<std::unique_ptr<XCEntity>> m_vEntities;
        std::unique_ptr<XCEntity> cloneEntity(const XCEntity* entity) const;
    };
}

#endif // XCPOLYLINE_H