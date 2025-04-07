#ifndef LINE_H
#define LINE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API Line : public Entity
    {
    public:
        Line();
        Line(const Ut::Vec2& start, const Ut::Vec2& end);
        ~Line() override;

    public:
        void clear();

        // 设置线段的两个端点
        void setPoints(const Ut::Vec2& start, const Ut::Vec2& end);

        // 设置终点
        void setEndPoint(const Ut::Vec2& end);

        // 获取顶点数据，用于绘制
        virtual std::pair<Ut::Vec2*, size_t> getData() const;
        virtual Ut::Rect2d& getRect();

        //std::pair<Ut::Vec2*, size_t> getData() const;

        // 获取端点
        void getPoints(Ut::Vec2& start, Ut::Vec2& end) const;
        void getEndPoint(Ut::Vec2& end) const;

        // 获取长度
        double getLength() const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // LINE_H