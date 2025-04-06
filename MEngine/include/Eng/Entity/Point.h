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
        void clear();

        // 设置点的位置
        void setPosition(const Ut::Vec2& position);

        // 获取顶点数据，用于绘制
        // std::pair<Ut::Vec2*, size_t> getData() const;

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