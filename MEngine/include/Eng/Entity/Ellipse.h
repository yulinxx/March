#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API Ellipse : public Entity
    {
    public:
        Ellipse();
        ~Ellipse() override;

    public:
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual void transform(const Ut::Mat3& matrix) override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Vec2d getValue(double t);
        virtual double EvalParam(const Ut::Vec2& p);

    public:
        // 设置椭圆：通过中心、长轴半径、短轴半径和旋转角度
        void setByCenterAxes(const Ut::Vec2& center, double majorRadius, double minorRadius,
            double rotation = 0.0, bool ccw = true);
        // 设置椭圆：通过边界框（矩形）
        void setByBoundingBox(const Ut::Vec2& bottomLeft, const Ut::Vec2& topRight);
        // 设置边数
        void setSides(size_t nSides);

        // 获取椭圆属性
        void getCenter(Ut::Vec2& center) const;
        void getAxes(double& majorRadius, double& minorRadius) const;
        double getRotation() const;
        bool isCounterClockwise() const;

    private:
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // ELLIPSE_H

#if 0
int main()
{
    MEngine::Ellipse ellipse;
    ellipse.setByBoundingBox(Ut::Vec2(-2.0, -1.0), Ut::Vec2(2.0, 1.0)); // 边界框：宽 4，高 2
    ellipse.setSides(32);

    renderEllipse(ellipse); // 中心 (0,0)，长轴 2，短轴 1，无旋转
    return 0;
}
#endif