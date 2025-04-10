#ifndef TEXT_H
#define TEXT_H

#include "Entity.h"
#include <string>

namespace MEngine
{
    class MENGINE_API Text : public Entity
    {
    public:
        Text();
        ~Text() override;

    public:
        virtual void clear() override;
        virtual double getLength() const override;

        virtual std::pair<Ut::Vec2*, size_t> getData() const
        {
            return std::pair<Ut::Vec2*, size_t>(nullptr, 0);
        }

        virtual Ut::Rect2d& getRect()
        {
            return Entity::getRect();
        }

        virtual Ut::Vec2d getValue(double t) override;
        virtual double EvalParam(const Ut::Vec2& p) override;

    public:
        // double BaseHeight;
        // std::string FontName;
        // double Height;
        // std::string text;
    };
}

#endif  // TEXT_H