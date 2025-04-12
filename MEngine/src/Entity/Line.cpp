#include "Entity/Line.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct Line::Impl
    {
        //Ut::Vec2 start;           // 起点
        Ut::Vec2 end;               // 终点
        std::vector<Ut::Vec2> vertices; // 顶点数据（两个点构成一条线段）
    };

    Line::Line()
    {
        init();
    }

    Line::Line(const Ut::Vec2& start, const Ut::Vec2& end)
    {
        init();
        setPoints(start, end);
    }

    Line::~Line()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Line::init()
    {
        m_impl = new Impl();

        setType(EntType::LINE);
        setClosed(false);
    }

    void Line::clear()
    {
        m_impl->vertices.clear();
        //m_impl->vertices.shrink_to_fit();
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
        updateVertices();
    }

    void Line::updateVertices()
    {
        clear();
        m_impl->vertices.push_back(getBasePoint());
        m_impl->vertices.push_back(m_impl->end);
    }

    std::pair<Ut::Vec2*, size_t> Line::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    Ut::Rect2d& Line::getRect()
    {
        auto& ptMin = getBasePoint();
        auto ptMax = m_impl->end;

        Ut::Rect2d rect{ ptMin, ptMax };
        setRect(rect);

        return Entity::getRect();
    }

    void Line::getPoints(Ut::Vec2& start, Ut::Vec2& end) const
    {
        start = getBasePoint();
        end = m_impl->end;
    }

    void Line::getStartPoint(Ut::Vec2& start) const
    {
        start = getBasePoint();
    }

    void Line::getEndPoint(Ut::Vec2& end) const
    {
        end = m_impl->end;
    }

    double Line::getLength() const
    {
        auto& start = getBasePoint();
        return (m_impl->end - start).length();
    }

    void Line::transform(const Ut::Mat3& matrix)
    {
        auto ptS = matrix.transformPoint(getBasePoint());
        auto ptE = matrix.transformPoint(m_impl->end);

        setBasePoint(ptS);
        m_impl->end = ptE;
        updateVertices();
    }

    Ut::Vec2d Line::getValue(double t)
    {
        auto dLen = getLength();
        double d = t / dLen;
        return getBasePoint() + (m_impl->end - getBasePoint()).normalize() * d;
    }

    double Line::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}