#include "Entity/Rectangle.h"
#include <array>

namespace MEngine
{
    struct Rectangle::Impl
    {
        Ut::Vec2 start;    // 起点
        Ut::Vec2 end;      // 终点
        std::array<Ut::Vec2, 5> vertices; // 矩形四个顶点
    };

    Rectangle::Rectangle()
    {
        m_impl = new Impl();
        setType(EntType::RECTANGLE);
    }

    Rectangle::~Rectangle()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Rectangle::clear()
    {
        m_impl->vertices.fill(Ut::Vec2(0, 0));
    }

    void Rectangle::setStartPoint(const Ut::Vec2& start)
    {
        clear();
        m_impl->start = start;
    }

    void Rectangle::setEndPoint(const Ut::Vec2& end)
    {
        m_impl->end = end;
        updateRect();
    }

    void Rectangle::setPts(const Ut::Vec2& start, const Ut::Vec2& end)
    {
        m_impl->start = start;
        m_impl->end = end;
        updateRect();
    }

    void Rectangle::updateRect()
    {
        // 计算四个顶点坐标
        m_impl->vertices[0] = m_impl->start;
        m_impl->vertices[1] = { m_impl->end.x(), m_impl->start.y() };
        m_impl->vertices[2] = m_impl->end;
        m_impl->vertices[3] = { m_impl->start.x(), m_impl->end.y() };

        closeRectangle();
    }

    void Rectangle::closeRectangle()
    {
        m_impl->vertices[4] = m_impl->start;
    }

    std::pair<Ut::Vec2*, size_t> Rectangle::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    Ut::Rect2d& Rectangle::getRect()
    {
        Ut::Rect2d rect(m_impl->start, m_impl->end);
        setRect(rect);
        return Entity::getRect();
    }

    double Rectangle::getLength() const
    {
        return 0.0;
    }

    void Rectangle::transform(const Ut::Mat3& matrix)
    {
        for (auto& pt : m_impl->vertices)
        {
            pt = matrix.transformPoint(pt);
        }

        // 更新起点和终点
        m_impl->start = m_impl->vertices[0];
        m_impl->end = m_impl->vertices[2];
    }

    Ut::Vec2d Rectangle::getValue(double t)
    {
        return getBasePoint();
    }

    double Rectangle::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}