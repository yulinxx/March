#ifndef ARC_H
#define ARC_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API Arc : public Entity
    {
    public:
        Arc();
        ~Arc() override;

    public:
        // 清空顶点数据
        void clear();

        // 设置圆弧：圆心、半径、起始角度、终止角度、方向
        void setByCenterRadius(const Ut::Vec2& center, double radius,
            double startAngle, double endAngle, bool ccw = true);

        // 设置圆弧：通过三点定义（起点、中点、终点）
        void setByThreePoints(const Ut::Vec2& start, const Ut::Vec2& mid, const Ut::Vec2& end);

        // 设置边数（控制平滑度）
        void setSides(size_t nSides);

        // 获取顶点数据，用于渲染
        virtual std::pair<Ut::Vec2*, size_t> getData() const;
        virtual Ut::Rect2d& getRect();

        // 获取圆弧属性
        void getRadius(double& radius) const;
        void getCenter(Ut::Vec2& center) const;
        void getAngles(double& startAngle, double& endAngle, bool& ccw) const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // ARC_H