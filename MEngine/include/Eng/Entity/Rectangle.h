#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"

namespace MEngine
{
    class MENGINE_API Rectangle : public Entity
    {
    public:
        Rectangle();
        ~Rectangle() override;

    public:
        virtual void clear() override;
        virtual std::pair<Ut::Vec2*, size_t> getData() const override; // 获取顶点数据，用于绘制

    public:
        void setStartPoint(const Ut::Vec2& start);
        void setEndPoint(const Ut::Vec2& end);
        void setPts(const Ut::Vec2& start, const Ut::Vec2& end);

    private:
        void updateRect();
        void closeRectangle();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // RECTANGLE_H  // 更新结尾注释