#include "Entity/Arc.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct Arc::Impl
    {
        Ut::Vec2 center;          // 圆心
        double radius = 0.0;      // 半径
        double startAngle = 0.0;  // 起始角度（弧度）
        double endAngle = 0.0;    // 终止角度（弧度）
        bool ccw = true;          // 逆时针方向
        size_t nSides = 32;       // 默认边数（中等平滑度）
        std::vector<Ut::Vec2> vertices; // 顶点数据
    };

    Arc::Arc()
    {
        init();
    }

    Arc::~Arc()
    {
        clear();
        delete m_impl;
        m_impl = nullptr;
    }

    void Arc::init()
    {
        m_impl = new Impl();
        setType(EntType::ARC);
        setClosed(false); // 圆弧不闭合
    }

    void Arc::clear()
    {
        m_impl->vertices.clear();
        //m_impl->vertices.shrink_to_fit();
    }

    void Arc::setByCenterRadius(const Ut::Vec2& center, double radius,
        double startAngle, double endAngle, bool ccw)
    {
        clear();

        if(fabs(startAngle - endAngle) < 1e-3)
            return;

        if (radius < 1e-6)
        {
            m_impl->radius = 0.0;
            return;
        }

        m_impl->center = center;
        m_impl->radius = radius;
        m_impl->startAngle = startAngle;
        m_impl->endAngle = endAngle;
        m_impl->ccw = ccw;

        updateVertices();
    }

    void Arc::setByThreePoints(const Ut::Vec2& start, const Ut::Vec2& mid, const Ut::Vec2& end)
    {
        clear();

        Ut::Vec2 vA = start - mid;
        Ut::Vec2 vB = end - mid;
        if(vA.cross(vB) < 1e-3) // 三点共线，无法确定圆弧
            return;

        // 计算圆心和半径
        double x1 = start.x(), y1 = start.y();
        double x2 = mid.x(), y2 = mid.y();
        double x3 = end.x(), y3 = end.y();

        // 计算垂直平分线的交点（圆心）
        double d = 2.0 * ((x1 - x3) * (y2 - y3) - (y1 - y3) * (x2 - x3));
        if (fabs(d) < 1e-3)
            return;

        double cx = ((y2 - y3) * (x1 * x1 + y1 * y1 - x3 * x3 - y3 * y3) -
            (y1 - y3) * (x2 * x2 + y2 * y2 - x3 * x3 - y3 * y3)) / d;

        double cy = ((x1 - x3) * (x2 * x2 + y2 * y2 - x3 * x3 - y3 * y3) -
            (x2 - x3) * (x1 * x1 + y1 * y1 - x3 * x3 - y3 * y3)) / d;

        m_impl->center = Ut::Vec2(cx, cy);
        m_impl->radius = (start - m_impl->center).length();

        // 计算起始角度和终止角度
        m_impl->startAngle = atan2(y1 - cy, x1 - cx);
        double midAngle = atan2(y2 - cy, x2 - cx);
        m_impl->endAngle = atan2(y3 - cy, x3 - cx);

        // 判断方向（通过叉积）
        Ut::Vec2 v1 = start - m_impl->center;
        Ut::Vec2 v2 = mid - m_impl->center;
        double cross = v1.x() * v2.y() - v1.y() * v2.x();
        m_impl->ccw = (cross > 0);

        // 调整角度范围
        if (m_impl->ccw)
        {
            if (midAngle < m_impl->startAngle)
                midAngle += 2.0 * Ut::PI;

            if (m_impl->endAngle < m_impl->startAngle)
                m_impl->endAngle += 2.0 * Ut::PI;

            if (midAngle > m_impl->endAngle)
                return;
        }
        else
        {
            if (midAngle > m_impl->startAngle)
                midAngle -= 2.0 * Ut::PI;

            if (m_impl->endAngle > m_impl->startAngle)
                m_impl->endAngle -= 2.0 * Ut::PI;

            if (midAngle < m_impl->endAngle)
                return;
        }

        updateVertices();
    }

    void Arc::setSides(size_t nSides)
    {
        if (m_impl->radius < 1e-3 || m_impl->nSides < 3)
            return;

        m_impl->nSides = nSides;
        updateVertices();
    }

    void Arc::updateVertices()
    {
        clear();

        if (m_impl->radius < 1e-3 || m_impl->nSides < 3)
            return;

        double startAng = m_impl->startAngle;
        double endAng = m_impl->endAngle;

        // 调整角度范围
        if (m_impl->ccw)
        {
            while (endAng < startAng)
                endAng += 2.0 * Ut::PI;
        }
        else
        {
            while (endAng > startAng)
                endAng -= 2.0 * Ut::PI;
        }

        double angleSpan = endAng - startAng;
        size_t numSegments = m_impl->nSides;

        // 生成顶点
        for (size_t i = 0; i <= numSegments; ++i)
        {
            double t = static_cast<double>(i) / numSegments;
            double angle = startAng + t * angleSpan;
            Ut::Vec2 vertex(
                m_impl->center.x() + m_impl->radius * cos(angle),
                m_impl->center.y() + m_impl->radius * sin(angle)
            );
            m_impl->vertices.emplace_back(vertex);
        }

        //setRect(Ut::Rect2d();
    }

    std::pair<Ut::Vec2*, size_t> Arc::getData() const
    {
        if (m_impl->vertices.empty() && m_impl->radius > 1e-3)
        {
            return { nullptr, 0 };
        }

        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    Ut::Rect2d& Arc::getRect()
    {
        Ut::Rect2d rect;
        if (m_impl->vertices.empty())
        {
            rect.setMin({ 0, 0 });
            rect.setMax({ 0, 0 });
            setRect(rect);
            return Entity::getRect();
        }

        double minX = m_impl->vertices[0].x();
        double minY = m_impl->vertices[0].y();
        double maxX = minX;
        double maxY = minY;

        for (const auto& vertex : m_impl->vertices)
        {
            minX = std::min(minX, vertex.x());
            minY = std::min(minY, vertex.y());
            maxX = std::max(maxX, vertex.x());
            maxY = std::max(maxY, vertex.y());
        }

        rect.setMin({ minX, minY });
        rect.setMax({ maxX, maxY });
        setRect(rect);
        return Entity::getRect();
    }


    //Ut::Vec2d Arc::getValue(double t)
    //{
    //    if (m_impl->radius < ARC_EPSILON)
    //    {
    //        return m_impl->center; // Arc is a point
    //    }

    //    // Clamp t to the range [0, 1] for standard behavior
    //    // Replace with std::clamp(t, 0.0, 1.0) if using C++17 or later
    //    if (t < 0.0) t = 0.0;
    //    if (t > 1.0) t = 1.0;

    //    double effStartAngle, effEndAngle;
    //    getEffectiveAngles(effStartAngle, effEndAngle);

    //    double angleSpan = effEndAngle - effStartAngle; // Can be positive (CCW) or negative (CW)

    //    // Handle zero span case (arc is effectively a point)
    //    if (fabs(angleSpan) < ARC_EPSILON)
    //    {
    //        return Ut::Vec2d(
    //            m_impl->center.x() + m_impl->radius * cos(effStartAngle),
    //            m_impl->center.y() + m_impl->radius * sin(effStartAngle)
    //        );
    //    }


    //    double currentAngle = effStartAngle + t * angleSpan;

    //    return Ut::Vec2d(
    //        m_impl->center.x() + m_impl->radius * cos(currentAngle),
    //        m_impl->center.y() + m_impl->radius * sin(currentAngle)
    //    );
    //}

    //double Arc::EvalParam(const Ut::Vec2& p)
    //{
    //    if (m_impl->radius < ARC_EPSILON)
    //    {
    //        return 0.0; // Closest point to a point arc is always at t=0 (or any t)
    //    }

    //    Ut::Vec2d vec = p - m_impl->center;
    //    // If p is the center, atan2 is undefined/0. Any point is equidistant. Return t=0.
    //    if (vec.length() < ARC_EPSILON * ARC_EPSILON)
    //    {
    //        return 0.0;
    //    }

    //    double pointAngle = atan2(vec.y(), vec.x());

    //    double effStartAngle, effEndAngle;
    //    getEffectiveAngles(effStartAngle, effEndAngle);
    //    double angleSpan = effEndAngle - effStartAngle; // Can be positive or negative

    //    // Handle full circle case (span is approx 2*PI)
    //    bool isFullCircle = (fabs(fabs(angleSpan) - 2.0 * M_PI) < ARC_EPSILON);
    //    if (isFullCircle)
    //    {
    //        // Normalize pointAngle relative to startAngle
    //        double normalizedAngle = pointAngle;
    //        while (normalizedAngle < effStartAngle - ARC_EPSILON) normalizedAngle += 2.0 * M_PI;
    //        while (normalizedAngle >= effStartAngle + 2.0 * M_PI - ARC_EPSILON) normalizedAngle -= 2.0 * M_PI;
    //        // Calculate t based on normalized angle
    //        double t = (normalizedAngle - effStartAngle) / angleSpan;
    //        // Clamp t due to potential floating point inaccuracies near boundaries
    //        if (t < 0.0) t = 0.0;
    //        if (t > 1.0) t = 1.0;
    //        // For CW full circle, need to adjust t? No, span is negative, should work.
    //        return t;
    //    }


    //    // Normalize pointAngle to be near the arc's span for easier comparison
    //    // Bring pointAngle into the range [effStartAngle - PI, effStartAngle + PI) approx
    //    double twoPi = 2.0 * M_PI;
    //    while (pointAngle < effStartAngle - M_PI) pointAngle += twoPi;
    //    while (pointAngle >= effStartAngle + M_PI) pointAngle -= twoPi;


    //    // Check if the angle corresponding to the closest point on the *circle*
    //    // falls within the *arc's* angular span.
    //    if (isAngleWithinSpan(pointAngle, effStartAngle, effEndAngle, m_impl->ccw))
    //    {
    //        // Angle is within the span, calculate t directly
    //        // Avoid division by zero if span is tiny
    //        if (fabs(angleSpan) < ARC_EPSILON) return 0.0; // Effectively a point arc

    //        double t = (pointAngle - effStartAngle) / angleSpan;

    //        // Clamp t due to potential floating point inaccuracies near boundaries
    //        if (t < 0.0) t = 0.0;
    //        if (t > 1.0) t = 1.0;
    //        return t;
    //    }
    //    else
    //    {
    //        // Angle is outside the span. Closest point is one of the endpoints.
    //        // Calculate squared distances to endpoints to avoid sqrt
    //        Ut::Vec2d startPoint = getValue(0.0);
    //        Ut::Vec2d endPoint = getValue(1.0);

    //        double distSqStart = (p - startPoint).length();
    //        double distSqEnd = (p - endPoint).length();

    //        return (distSqStart <= distSqEnd) ? 0.0 : 1.0;
    //    }
    //}


    void Arc::getRadius(double& radius) const
    {
        radius = m_impl->radius;
    }

    void Arc::getCenter(Ut::Vec2& center) const
    {
        center = m_impl->center;
    }

    void Arc::getAngles(double& startAngle, double& endAngle) const
    {
        startAngle = m_impl->startAngle;
        endAngle = m_impl->endAngle;
    }

    double Arc::getStartAngle() const {
        return m_impl->startAngle;
    }

    double Arc::getEndAngle() const {
        return m_impl->endAngle;
    }

    bool Arc::isCCW() const 
    {
        return m_impl->ccw;
    }
}