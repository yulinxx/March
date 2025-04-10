#include "Entity/Point.h"
#include <stdexcept>

namespace MEngine
{
    struct Point::Impl
    {
        // Ut::Vec2 position;         // 点的位置
        // std::vector<Ut::Vec2> vertices; // 顶点数据（仅一个点）
    };

    Point::Point()
    {
        m_impl = new Impl();
        setType(EntType::POINT);
        setClosed(false); // 点不闭合
    }

    Point::~Point()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Point::clear()
    {
        //m_impl->vertices.clear();
        //m_impl->vertices.shrink_to_fit();
    }

    void Point::setPosition(const Ut::Vec2& position)
    {
        clear();
        setBasePoint(position);
        // m_impl->position = position;
        updateVertex();
    }

    void Point::updateVertex()
    {
        // clear();
        // m_impl->vertices.push_back(m_impl->position);
    }

    // std::pair<Ut::Vec2*, size_t> Point::getData() const
    // {
    //     return { m_impl->vertices.data(), m_impl->vertices.size() };
    // }

    std::pair<Ut::Vec2*, size_t> Point::getData() const
    {
        return { &getBasePoint(), 1 };
    }

    Ut::Rect2d& Point::getRect()
    {
        auto& ptMin = getBasePoint();
        Ut::Rect2d rect({ ptMin, ptMin });
        setRect(rect);

        return getRect();
    }

    Ut::Vec2 Point::getPosition() const
    {
        return getBasePoint();
    }

    double Point::getLength() const
    {
        return 0.0;
    }

    Ut::Vec2d Point::getValue(double t)
    {
        return getBasePoint();
    }

    double Point::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}