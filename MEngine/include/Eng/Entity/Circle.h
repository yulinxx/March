#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API Circle : public Entity
    {
    public:
        Circle();
        ~Circle() override;

    public:
        void clear();

        // 设置圆：通过圆心和圆上一点
        void setByCenterPt(const Ut::Vec2& center, const Ut::Vec2& end, bool ccw = true);
        // 设置圆：通过圆心和半径
        void setByCenterRadius(const Ut::Vec2& center, double radius, bool ccw = true);
        // 设置圆：通过直径两点
        void setByDiameter(const Ut::Vec2& start, const Ut::Vec2& end);
        // 设置圆：通过圆周上三点
        void setByThreePoints(const Ut::Vec2& p1, const Ut::Vec2& p2, const Ut::Vec2& p3);
        // 设置边数
        void setSides(size_t nSides);

        // 获取顶点数据，用于绘制
        std::pair<Ut::Vec2*, size_t> getData() const;

        // 获取圆属性
        void getRadius(double& radius) const;
        void getCenter(Ut::Vec2& center) const;
        bool isCCW() const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // CIRCLE_H