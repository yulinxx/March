#include "Entity/PolyLine.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct PolyLine::Impl
    {
        std::vector<Ut::Vec2> vertices;
    };

    PolyLine::PolyLine()
    {
        m_impl = new Impl();

        setType(EntType::LWPOLYLINE);
        setClosed(false);
    }

    PolyLine::PolyLine(const std::vector<Ut::Vec2>& points, bool closed)
    {
        m_impl = new Impl();
        setType(EntType::LWPOLYLINE);
        setPoints(points, closed);
    }

    PolyLine::~PolyLine()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void PolyLine::clear()
    {
        m_impl->vertices.clear();
        m_impl->vertices.shrink_to_fit();
    }

    void PolyLine::setPoints(const std::vector<Ut::Vec2>& points, bool closed)
    {
        if (points.size() < 2)
        {
            return;
        }
        clear();
        m_impl->vertices = points;
        setClosed(closed);
        updateVertices();
    }

    void PolyLine::addPoint(const Ut::Vec2& point)
    {
        m_impl->vertices.push_back(point);
        updateVertices();
    }

    void PolyLine::setClosed(bool closed)
    {
        Entity::setClosed(closed);
        updateVertices();
    }

    void PolyLine::updateVertices()
    {
        m_impl->vertices.clear();
        if (m_impl->vertices.size() < 2)
        {
            return;
        }

        if (isClosed())
        {
            m_impl->vertices.push_back(m_impl->vertices.front());
        }
    }

    std::pair<Ut::Vec2*, size_t> PolyLine::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    double PolyLine::getLength() const
    {
        if (m_impl->vertices.size() < 2)
        {
            return 0.0;
        }

        double totalLength = 0.0;
        for (size_t i = 1; i < m_impl->vertices.size(); ++i)
        {
            auto ptA = m_impl->vertices[i - 1];
            auto ptB = m_impl->vertices[i];
            totalLength += (ptB - ptA).length();
        }

        return totalLength;
    }

    Ut::Rect2d& PolyLine::getRect()
    {
        Ut::Rect2d rect;
        for (auto pt : m_impl->vertices)
        {
            rect.expand(pt);
        }

        setRect(rect);
        return Entity::getRect();
    }

    Ut::Vec2d PolyLine::getValue(double t)
    {
        return getBasePoint();
    }

    double PolyLine::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}