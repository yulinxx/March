#include "Entity/Polygon.h"
#include <vector>

namespace MEngine
{
    struct Polygon::Impl
    {
        Ut::Vec2 start;    // 起点
        Ut::Vec2 end;      // 终点
        size_t nSides = 5; // 边数，默认为 5
        std::vector<Ut::Vec2> vVertices;
    };

    Polygon::Polygon()
    {
        m_impl = new Impl();
        setType(EntType::POLYGON);
    }

    Polygon::~Polygon()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Polygon::clear()
    {
        m_impl->vVertices.clear();
        m_impl->vVertices.shrink_to_fit();
    }

    void Polygon::setStartPoint(const Ut::Vec2& start)
    {
        clear();
        m_impl->start = start;
    }

    void Polygon::setEndPoint(const Ut::Vec2& end)
    {
        m_impl->end = end;
        updatePolygon();
    }

    void Polygon::setPts(const Ut::Vec2& start, const Ut::Vec2& end, size_t nSides)
    {
        m_impl->start = start;
        m_impl->end = end;
        m_impl->nSides = nSides;
        updatePolygon();
    }

    void Polygon::setSide(size_t nSides)
    {
        m_impl->nSides = nSides;
    }

    void Polygon::updatePolygon()
    {
        clear();

        const int& nSides = m_impl->nSides;
        const Ut::Vec2d& center = m_impl->start;
        const Ut::Vec2d& endPt = m_impl->end;

        // 计算半径和起始角度（根据第二个点确定）
        const double dx = endPt.x() - center.x();
        const double dy = endPt.y() - center.y();

        //const double radius = sqrt(dx * dx + dy * dy);
        const double radius = (center - endPt).length();

        const double startAngle = atan2(dy, dx);  // 获取第二个点相对中心的极角

        for (int i = 0; i < nSides; ++i)
        {
            // 从起始角度开始均匀分布顶点
            double angle = startAngle + 2 * Ut::PI * i / nSides;
            Ut::Vec2d vertex(
                center.x() + radius * cos(angle),
                center.y() + radius * sin(angle)
            );

            m_impl->vVertices.push_back(vertex);
        }

        closePolygon();
    }

    void Polygon::closePolygon()
    {
        if (m_impl->vVertices.size() > 2)
        {
            m_impl->vVertices.push_back(m_impl->vVertices.front());
        }
    }

    std::pair<Ut::Vec2*, size_t> Polygon::getData() const
    {
        return { m_impl->vVertices.data(), m_impl->vVertices.size() };
    }
}