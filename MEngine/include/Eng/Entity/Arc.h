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

        ////获取参数 t (0-1) 对应的点
        //virtual Ut::Vec2d getValue(double t) override;

        //// 获取点 p 在圆弧上最近点的参数 t (0-1)
        //virtual double EvalParam(const Ut::Vec2& p) override;

        // 获取顶点数据，用于渲染
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Rect2d& getRect() override;

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