#include "Entity/PolyLine.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct PolyLine::Impl
    {
        std::vector<Ut::Vec2> points;
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
        m_impl->points.clear();
        m_impl->vertices.clear();
        m_impl->points.shrink_to_fit();
        m_impl->vertices.shrink_to_fit();
    }

    void PolyLine::setPoints(const std::vector<Ut::Vec2>& points, bool closed)
    {
        if (points.size() < 2)
        {
            return;
        }
        clear();
        m_impl->points = points;
        setClosed(closed);
        updateVertices();
    }

    void PolyLine::addPoint(const Ut::Vec2& point)
    {
        m_impl->points.push_back(point);
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
        if (m_impl->points.size() < 2)
        {
            return;
        }

        // 添加所有顶点
        m_impl->vertices = m_impl->points;

        // 如果闭合，添加第一个点以闭合折线
        if (isClosed() && !m_impl->points.empty())
        {
            m_impl->vertices.push_back(m_impl->points.front());
        }
    }

    std::pair<Ut::Vec2*, size_t> PolyLine::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    std::vector<Ut::Vec2> PolyLine::getPoints() const
    {
        return m_impl->points;
    }

    double PolyLine::getLength() const
    {
        if (m_impl->points.size() < 2)
        {
            return 0.0;
        }

        double totalLength = 0.0;
        for (size_t i = 1; i < m_impl->points.size(); ++i)
        {
            double dx = m_impl->points[i].x() - m_impl->points[i - 1].x();
            double dy = m_impl->points[i].y() - m_impl->points[i - 1].y();
            totalLength += sqrt(dx * dx + dy * dy);
        }

        // 如果闭合，计算首尾之间的长度
        if (isClosed() && m_impl->points.size() >= 2)
        {
            double dx = m_impl->points.front().x() - m_impl->points.back().x();
            double dy = m_impl->points.front().y() - m_impl->points.back().y();
            totalLength += sqrt(dx * dx + dy * dy);
        }

        return totalLength;
    }
}