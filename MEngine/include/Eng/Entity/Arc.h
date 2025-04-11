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
        // 清空数据
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual void transform(const Ut::Mat3& matrix) override;
        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        // 设置圆弧：圆心、半径、起始角度、终止角度、方向
        void setByCenterRadius(const Ut::Vec2& center, double radius,
            double startAngle, double endAngle, bool ccw = true);

        // 设置圆弧：通过三点定义（起点、中点、终点）
        void setByThreePoints(const Ut::Vec2& start, const Ut::Vec2& mid, const Ut::Vec2& end);

        // 设置边数（控制平滑度）
        void setSides(size_t nSides);

        // 获取圆弧属性
        void getRadius(double& radius) const;
        void getCenter(Ut::Vec2& center) const;
        void getAngles(double& startAngle, double& endAngle) const;
        double getStartAngle() const; // 获取起始角度
        double getEndAngle() const; // 获取终止角度
        bool isCCW() const; // 获取方向

    private:
        void init();
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // ARC_H