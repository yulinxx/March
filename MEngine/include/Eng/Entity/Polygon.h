#ifndef POLYGON_H
#define POLYGON_H

#include "Entity.h"

namespace MEngine
{
    class MENGINE_API Polygon : public Entity
    {
    public:
        Polygon();
        ~Polygon() override; // 需要显式声明析构

    public:
        void clear();
        void addVertex(const Ut::Vec2& vertex);
        
        void closePolygon();

        std::pair<Ut::Vec2*, size_t> getLinesData() const;

    private:
        struct Impl;
        Impl* m_impl;

        // 保留可能需要重写的接口
        // Ut::Vec2 getValue(double t) override;
        // double EvalParam(const Ut::Vec2& p) override;
    };
}

#endif // POLYGON_H