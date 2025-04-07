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
        m_impl = new Impl();
        setType(EntType::ARC);
        setClosed(false); // 圆弧不闭合
    }

    Arc::~Arc()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Arc::clear()
    {
        m_impl->vertices.clear();
        m_impl->vertices.shrink_to_fit();
    }

    void Arc::setByCenterRadius(const Ut::Vec2& center, double radius,
        double startAngle, double endAngle, bool ccw)
    {
        if (radius < 1e-3)
            return;

        clear();

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
        if (nSides < 3)
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
            m_impl->vertices.push_back(vertex);
        }

        //setRect(Ut::Rect2d();
    }

    std::pair<Ut::Vec2*, size_t> Arc::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    Ut::Rect2d& Arc::getRect()
    {

        // 计算起始点和终止点坐标
        Ut::Vec2 startPoint = {
            m_impl->center.x() + m_impl->radius * cos(m_impl->startAngle),
            m_impl->center.y() + m_impl->radius * sin(m_impl->startAngle)
        };

        Ut::Vec2 endPoint = {
            m_impl->center.x() + m_impl->radius * cos(m_impl->endAngle),
            m_impl->center.y() + m_impl->radius * sin(m_impl->endAngle)
        };

        // 角度归一化处理
        double normalizedStart = fmod(m_impl->startAngle, 2 * Ut::PI);
        double normalizedEnd = fmod(m_impl->endAngle, 2 * Ut::PI);

        if (normalizedEnd < normalizedStart)
            normalizedEnd += 2 * Ut::PI;

        // 判断是否跨越关键角度
        bool crosses0 = (normalizedStart <= 0 && normalizedEnd >= 0) ||
            (normalizedStart <= 2 * Ut::PI && normalizedEnd >= 2 * Ut::PI);

        bool crosses90 = normalizedStart <= Ut::PI / 2 && normalizedEnd >= Ut::PI / 2;
        bool crosses180 = normalizedStart <= Ut::PI && normalizedEnd >= Ut::PI;
        bool crosses270 = normalizedStart <= 3 * Ut::PI / 2 && normalizedEnd >= 3 * Ut::PI / 2;

        // 计算边界值
        double right = crosses0 ? (m_impl->center.x() + m_impl->radius) : std::max(startPoint.x(), endPoint.x());
        double left = crosses180 ? (m_impl->center.x() - m_impl->radius) : std::min(startPoint.x(), endPoint.x());
        double top = crosses90 ? (m_impl->center.y() + m_impl->radius) : std::max(startPoint.y(), endPoint.y());
        double bottom = crosses270 ? (m_impl->center.y() - m_impl->radius) : std::min(startPoint.y(), endPoint.y());

        // 包围框结果
        Ut::Rect2d rect = { {left, top}, {right - left, top - bottom } };

        //auto rect = Ut::Rect2d(Ut::Vec2d(minX, minY), Ut::Vec2d(maxX, maxY));
        //setRect(rect); 

        return getRect();
    }

    void Arc::getRadius(double& radius) const
    {
        radius = m_impl->radius;
    }

    void Arc::getCenter(Ut::Vec2& center) const
    {
        center = m_impl->center;
    }

    void Arc::getAngles(double& startAngle, double& endAngle, bool& ccw) const
    {
        startAngle = m_impl->startAngle;
        endAngle = m_impl->endAngle;
        ccw = m_impl->ccw;
    }
}