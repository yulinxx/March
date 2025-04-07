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
        void clear();

        void setStartPoint(const Ut::Vec2& start);
        void setEndPoint(const Ut::Vec2& end);
        void setPts(const Ut::Vec2& start, const Ut::Vec2& end);

        //std::pair<Ut::Vec2*, size_t> getData() const;
        virtual std::pair<Ut::Vec2*, size_t> getData() const;
        //virtual Ut::Rect2d& getRect();

    private:
        void updateRect();
        void closeRectangle();

    private:
        struct Impl;
        Impl* m_impl;
    };
}

#endif // RECTANGLE_H  // 更新结尾注释