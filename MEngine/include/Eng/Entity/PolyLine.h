#ifndef POLYLINE_H
#define POLYLINE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API PolyLine : public Entity
    {
    public:
        PolyLine();
        PolyLine(const std::vector<Ut::Vec2>& points, bool closed = false);
        ~PolyLine() override;

    public:
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        // 设置所有顶点
        void setPoints(const std::vector<Ut::Vec2>& points, bool closed = false);
        // 添加单个顶点
        void addPoint(const Ut::Vec2& point);
        // 设置是否闭合
        void setClosed(bool closed);

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // POLYLINE_H