#ifndef POINT_H
#define POINT_H

#include "Entity.h"
#include <vector>

namespace MEngine
{
    class MENGINE_API Point : public Entity
    {
    public:
        Point();
        ~Point() override;

    public:
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual void transform(const Ut::Mat3& matrix) override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        // 设置点的位置
        void setPosition(const Ut::Vec2& position);
        // 获取点的位置
        Ut::Vec2 getPosition() const;

    private:
        void updateVertex();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // POINT_H