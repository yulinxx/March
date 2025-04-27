#include "Entity/Circle.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct Circle::Impl
    {
        Ut::Vec2 center;          // 圆心
        double radius = 0.0;      // 半径
        size_t nSides = 32;       // 默认边数（CAD 中适中值）
        bool ccw = true;          // 逆时针方向
        std::vector<Ut::Vec2> vertices; // 顶点数据
    };

    Circle::Circle()
    {
        m_impl = new Impl();
        setType(EntType::CIRCLE);
        setClosed(true); // 圆是闭合的
    }

    Circle::~Circle()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Circle::clear()
    {
        m_impl->vertices.clear();
        //m_impl->vertices.shrink_to_fit();
    }

    void Circle::setByCenterPt(const Ut::Vec2& center, const Ut::Vec2& end, bool ccw /*=true*/)
    {
        clear();
        double radius = (end - center).length();
        if (radius < 1e-3)
            return;

        m_impl->center = center;
        m_impl->radius = radius;
        m_impl->ccw = ccw;
        updateVertices();
    }

    void Circle::setByCenterRadius(const Ut::Vec2& center, double radius, bool ccw)
    {
        clear();
        if (radius < 1e-3)
            return;

        m_impl->center = center;
        m_impl->radius = radius;
        m_impl->ccw = ccw;
        updateVertices();
    }

    void Circle::setByDiameter(const Ut::Vec2& start, const Ut::Vec2& end)
    {
        clear();
        m_impl->radius = (start - end).length();
        if (m_impl->radius < 1e-3)
        {
            return;
        }

        m_impl->center = Ut::Vec2((start.x() + end.x()) / 2.0, (start.y() + end.y()) / 2.0);
        updateVertices();
    }

    void Circle::setByThreePoints(const Ut::Vec2& p1, const Ut::Vec2& p2, const Ut::Vec2& p3)
    {
        clear();

        // 计算圆心（垂直平分线交点）
        double x1 = p1.x(), y1 = p1.y();
        double x2 = p2.x(), y2 = p2.y();
        double x3 = p3.x(), y3 = p3.y();

        double d = 2.0 * ((x1 - x3) * (y2 - y3) - (y1 - y3) * (x2 - x3));
        if (fabs(d) < 1e-3)
            return;

        double cx = ((y2 - y3) * (x1 * x1 + y1 * y1 - x3 * x3 - y3 * y3) -
            (y1 - y3) * (x2 * x2 + y2 * y2 - x3 * x3 - y3 * y3)) / d;
        double cy = ((x1 - x3) * (x2 * x2 + y2 * y2 - x3 * x3 - y3 * y3) -
            (x2 - x3) * (x1 * x1 + y1 * y1 - x3 * x3 - y3 * y3)) / d;

        m_impl->center = Ut::Vec2(cx, cy);
        m_impl->radius = (p1 - m_impl->center).length();
        updateVertices();
    }

    void Circle::setSides(size_t nSides)
    {
        if (nSides < 3)
            nSides = 3;

        m_impl->nSides = nSides;
        updateVertices();
    }

    void Circle::updateVertices()
    {
        clear();

        if (m_impl->radius < 1e-3 || m_impl->nSides < 3)
            return;

        // 生成圆的顶点
        size_t numSegments = m_impl->nSides;
        double angleStep = 2.0 * Ut::PI / numSegments;
        if (!m_impl->ccw)
        {
            angleStep = -angleStep; // 顺时针方向
        }

        for (size_t i = 0; i <= numSegments; ++i)
        {
            // 多生成一个点以闭合
            double angle = i * angleStep;
            Ut::Vec2 vertex(
                m_impl->center.x() + m_impl->radius * cos(angle),
                m_impl->center.y() + m_impl->radius * sin(angle)
            );
            m_impl->vertices.push_back(vertex);
        }
    }

    void Circle::transform(const Ut::Mat3& matrix)
    {
        // 变换圆心坐标
        m_impl->center = matrix.transformPoint(m_impl->center);

        //double scale = sqrt(matrix[0][0]*matrix[0][0] + matrix[0][1]*matrix[0][1]);
        //m_impl->radius *= scale;

        // 更新顶点数据
        updateVertices();
    }

    std::pair<Ut::Vec2*, size_t> Circle::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    Ut::Rect2d& Circle::getRect()
    {
        auto ptMin = Ut::Vec2d(m_impl->center.x() - m_impl->radius, m_impl->center.y() - m_impl->radius);
        auto ptMax = Ut::Vec2d(m_impl->center.x() + m_impl->radius, m_impl->center.y() + m_impl->radius);
        Ut::Rect2d rect{ ptMin, ptMax };
        setRect(rect);
        return Entity::getRect();
    }

    void Circle::getRadius(double& radius) const
    {
        radius = m_impl->radius;
    }

    void Circle::getCenter(Ut::Vec2& center) const
    {
        center = m_impl->center;
    }

    double Circle::getLength() const
    {
        return 2.0 * Ut::PI * m_impl->radius;
    }

    bool Circle::isCCW() const
    {
        return m_impl->ccw;
    }

    Ut::Vec2d Circle::getValue(double t)
    {
        return getBasePoint();
    }

    double Circle::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}