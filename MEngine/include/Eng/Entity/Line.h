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
        virtual void clear() override;
        virtual double getLength() const override;
        virtual Ut::Rect2d& getRect() override;
        virtual void transform(const Ut::Mat3& matrix) override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override;
        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        // 设置线段的两个端点
        void setPoints(const Ut::Vec2& start, const Ut::Vec2& end);

        // 设置终点
        void setEndPoint(const Ut::Vec2& end);

        //std::pair<Ut::Vec2*, size_t> getData() const;

        // 获取端点
        void getPoints(Ut::Vec2& start, Ut::Vec2& end) const;
        void getEndPoint(Ut::Vec2& end) const;

    private:
        void init();
        void updateVertices();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // LINE_H