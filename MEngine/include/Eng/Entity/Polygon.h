#ifndef POLYGON_H
#define POLYGON_H

#include "Entity.h"

namespace MEngine
{
    class MENGINE_API Polygon : public Entity
    {
    public:
        Polygon();
        ~Polygon() override;

    public:
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual void transform(const Ut::Mat3& matrix) override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        // void addVertex(const Ut::Vec2& vertex);

        void setStartPoint(const Ut::Vec2& start);
        void setEndPoint(const Ut::Vec2& end);

        void setPts(const Ut::Vec2& start, const Ut::Vec2& end, size_t nSides = 5);
        void setSide(size_t nSides);

    private:
        void updatePolygon();
        void closePolygon();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // POLYGON_H