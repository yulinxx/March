#include "Entity/Line.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct Line::Impl
    {
        //Ut::Vec2 start;           // 起点
        Ut::Vec2 end;             // 终点
        std::vector<Ut::Vec2> vertices; // 顶点数据（两个点）
    };

    Line::Line()
    {
        m_impl = new Impl();

        setType(EntType::LINE);
        setClosed(false);
    }

    Line::Line(const Ut::Vec2& start, const Ut::Vec2& end)
    {
        setPoints(start, end);
    }

    Line::~Line()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Line::clear()
    {
        m_impl->vertices.clear();
        m_impl->vertices.shrink_to_fit();
    }

    void Line::setPoints(const Ut::Vec2& start, const Ut::Vec2& end)
    {
        clear();
        setBasePoint(start);
        m_impl->end = end;
        updateVertices();
    }

    void Line::setEndPoint(const Ut::Vec2& end)
    {
        m_impl->end = end;
    }

    void Line::updateVertices()
    {
        clear();
        auto& start = getBasePoint();
        m_impl->vertices.push_back(start);
        m_impl->vertices.push_back(m_impl->end);
    }

    std::pair<Ut::Vec2*, size_t> Line::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    void Line::getPoints(Ut::Vec2& start, Ut::Vec2& end) const
    {
        start = getBasePoint();
        end = m_impl->end;
    }

    void Line::getEndPoint(Ut::Vec2& end) const
    {
        end = m_impl->end;
    }

    double Line::getLength() const
    {
        auto& start = getBasePoint();
        double dx = m_impl->end.x() - start.x();
        double dy = m_impl->end.y() - start.y();
        return sqrt(dx * dx + dy * dy);
    }
}