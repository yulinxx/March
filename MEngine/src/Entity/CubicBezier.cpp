#include "Entity/CubicBezier.h"
#include "3rd/bezier.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct CubicBezier::Impl
    {
        Ut::Vec2 p0;              // 起点
        Ut::Vec2 p1;              // 第一个控制点
        Ut::Vec2 p2;              // 第二个控制点
        Ut::Vec2 p3;              // 终点
        size_t nSegments = 32;    // 默认采样点数
        std::vector<Ut::Vec2> vertices; // 顶点数据
    };

    CubicBezier::CubicBezier()
    {
        m_impl = new Impl();
        setType(EntType::BEZIER);
        setClosed(false); // 贝塞尔曲线不闭合
    }

    CubicBezier::~CubicBezier()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void CubicBezier::clear()
    {
        m_impl->vertices.clear();
        m_impl->vertices.shrink_to_fit();
    }

    void CubicBezier::setByControlPoints(const Ut::Vec2& p0, const Ut::Vec2& p1,
        const Ut::Vec2& p2, const Ut::Vec2& p3)
    {
        clear();
        m_impl->p0 = p0;
        m_impl->p1 = p1;
        m_impl->p2 = p2;
        m_impl->p3 = p3;
        updateVertices();
    }

    void CubicBezier::setSegments(size_t nSegments)
    {
        if (nSegments < 2)
            nSegments = 2;

        m_impl->nSegments = nSegments;
        updateVertices();
    }

    void CubicBezier::updateVertices()
    {
        clear();

        if (m_impl->nSegments < 2)
            m_impl->nSegments = 2;

        // 生成贝塞尔曲线顶点
        for (size_t i = 0; i <= m_impl->nSegments; ++i)
        {
            double t = static_cast<double>(i) / m_impl->nSegments;
            Ut::Vec2 point = evaluate(t);
            m_impl->vertices.push_back(point);
        }
    }

    Ut::Vec2 CubicBezier::evaluate(double t) const
    {
        if (t < 0.0)
            t = 0.0;
        if (t > 1.0)
            t = 1.0;

        // 三阶贝塞尔曲线公式：
        // B(t) = (1-t)^3 * P0 + 3(1-t)^2 * t * P1 + 3(1-t) * t^2 * P2 + t^3 * P3
        double t2 = t * t;
        double t3 = t2 * t;
        double mt = 1.0 - t;
        double mt2 = mt * mt;
        double mt3 = mt2 * mt;

        double x = mt3 * m_impl->p0.x() + 3.0 * mt2 * t * m_impl->p1.x() +
            3.0 * mt * t2 * m_impl->p2.x() + t3 * m_impl->p3.x();
        double y = mt3 * m_impl->p0.y() + 3.0 * mt2 * t * m_impl->p1.y() +
            3.0 * mt * t2 * m_impl->p2.y() + t3 * m_impl->p3.y();

        return Ut::Vec2(x, y);
    }

    std::pair<Ut::Vec2*, size_t> CubicBezier::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    Ut::Rect2d& CubicBezier::getRect()
    {
        std::vector<bezier::Point> vPts;
        vPts.emplace_back(bezier::Vec2(m_impl->p0.x(), m_impl->p0.y()));
        vPts.emplace_back(bezier::Vec2(m_impl->p1.x(), m_impl->p1.y()));
        vPts.emplace_back(bezier::Vec2(m_impl->p2.x(), m_impl->p2.y()));
        vPts.emplace_back(bezier::Vec2(m_impl->p3.x(), m_impl->p3.y()));

        bezier::Bezier<3> bezier(vPts);
        double dLen = bezier.length();
        auto aabb = bezier.aabb();
        double dMinX = aabb.minX();
        double dMinY = aabb.minY();
        double dMaxX = aabb.maxX();
        double dMaxY = aabb.maxY();
        Ut::Rect2d rect({ dMinX, dMinY }, { dMaxX, dMaxY });
        Entity::setRect(rect);
        return Entity::getRect();
    }

    void CubicBezier::getControlPoints(Ut::Vec2& p0, Ut::Vec2& p1,
        Ut::Vec2& p2, Ut::Vec2& p3) const
    {
        p0 = m_impl->p0;
        p1 = m_impl->p1;
        p2 = m_impl->p2;
        p3 = m_impl->p3;
    }

    double CubicBezier::getLength() const
    {
        std::vector<bezier::Point> vPts;
        vPts.emplace_back(bezier::Vec2(m_impl->p0.x(), m_impl->p0.y()));
        vPts.emplace_back(bezier::Vec2(m_impl->p1.x(), m_impl->p1.y()));
        vPts.emplace_back(bezier::Vec2(m_impl->p2.x(), m_impl->p2.y()));
        vPts.emplace_back(bezier::Vec2(m_impl->p3.x(), m_impl->p3.y()));

        bezier::Bezier<3> bezier(vPts);
        double dLen = bezier.length();
        return dLen;
    }
    void CubicBezier::transform(const Ut::Mat3& matrix)
    {
        
    }
    Ut::Vec2d CubicBezier::getValue(double t)
    {
        return getBasePoint();
    }

    double CubicBezier::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}