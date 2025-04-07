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
        void clear();

        // 设置所有顶点
        void setPoints(const std::vector<Ut::Vec2>& points, bool closed = false);
        // 添加单个顶点
        void addPoint(const Ut::Vec2& point);
        // 设置是否闭合
        void setClosed(bool closed);

        // 获取顶点数据，用于绘制
        //std::pair<Ut::Vec2*, size_t> getData() const;
        virtual std::pair<Ut::Vec2*, size_t> getData() const;
        //virtual Ut::Rect2d& getRect();

        // 获取所有顶点
        std::vector<Ut::Vec2> getPoints() const;

        // 获取总长度
        double getLength() const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // POLYLINE_H