#include "Entity/Ellipse.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct Ellipse::Impl
    {
        Ut::Vec2 center;                // 中心点
        double majorRadius = 0.0;       // 长轴半径 (a)
        double minorRadius = 0.0;       // 短轴半径 (b)
        double rotation = 0.0;          // 旋转角度（弧度）
        size_t nSides = 32;             // 默认边数
        bool ccw = true;                // 逆时针方向
        std::vector<Ut::Vec2> vertices; // 顶点数据
    };

    Ellipse::Ellipse()
    {
        m_impl = new Impl();
        setType(EntType::ELLIPSE);
        setClosed(true); // 椭圆是闭合的
    }

    Ellipse::~Ellipse()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void Ellipse::clear()
    {
        m_impl->vertices.clear();
        m_impl->vertices.shrink_to_fit();
    }

    void Ellipse::setByCenterAxes(const Ut::Vec2& center, double majorRadius, double minorRadius,
        double rotation, bool ccw)
    {
        if (majorRadius < 1e-6 || minorRadius < 1e-6)
        {
            // throw std::runtime_error("Radii must be positive");
            return;
        }
        if (majorRadius < minorRadius)
        {
            // 确保 majorRadius 是长轴
            std::swap(majorRadius, minorRadius);
            rotation += Ut::PI / 2.0; // 调整旋转角度
        }
        clear();
        m_impl->center = center;
        m_impl->majorRadius = majorRadius;
        m_impl->minorRadius = minorRadius;
        m_impl->rotation = rotation;
        m_impl->ccw = ccw;
        updateVertices();
    }

    void Ellipse::setByBoundingBox(const Ut::Vec2& bottomLeft, const Ut::Vec2& topRight)
    {
        clear();
        double width = topRight.x() - bottomLeft.x();
        double height = topRight.y() - bottomLeft.y();
        if (width < 1e-6 || height < 1e-6)
        {
            // throw std::runtime_error("Bounding box dimensions must be positive");
            return;
        }

        m_impl->center = Ut::Vec2(
            (bottomLeft.x() + topRight.x()) / 2.0,
            (bottomLeft.y() + topRight.y()) / 2.0);
        m_impl->majorRadius = width / 2.0;
        m_impl->minorRadius = height / 2.0;
        m_impl->rotation = 0.0; // 默认无旋转

        if (m_impl->majorRadius < m_impl->minorRadius)
        {
            std::swap(m_impl->majorRadius, m_impl->minorRadius);
            m_impl->rotation = Ut::PI / 2.0;
        }

        updateVertices();
    }

    void Ellipse::setSides(size_t nSides)
    {
        if (nSides < 3)
        {
            // throw std::runtime_error("Number of sides must be at least 3");
            return;
        }
        m_impl->nSides = nSides;
        updateVertices();
    }

    void Ellipse::updateVertices()
    {
        clear();

        if (m_impl->majorRadius < 1e-6 || m_impl->minorRadius < 1e-6 || m_impl->nSides < 3)
        {
            return;
        }

        size_t numSegments = m_impl->nSides;
        double angleStep = 2.0 * Ut::PI / numSegments;
        if (!m_impl->ccw)
        {
            angleStep = -angleStep; // 顺时针方向
        }

        // 生成椭圆的参数化顶点
        for (size_t i = 0; i <= numSegments; ++i)
        { // 多生成一个点以闭合
            double t = i * angleStep;
            double x = m_impl->majorRadius * cos(t);
            double y = m_impl->minorRadius * sin(t);

            // 应用旋转
            double rotX = x * cos(m_impl->rotation) - y * sin(m_impl->rotation);
            double rotY = x * sin(m_impl->rotation) + y * cos(m_impl->rotation);

            // 平移到中心
            Ut::Vec2 vertex(
                m_impl->center.x() + rotX,
                m_impl->center.y() + rotY);
            m_impl->vertices.push_back(vertex);
        }
    }

    std::pair<Ut::Vec2*, size_t> Ellipse::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    void Ellipse::getCenter(Ut::Vec2& center) const
    {
        center = m_impl->center;
    }

    void Ellipse::getAxes(double& majorRadius, double& minorRadius) const
    {
        majorRadius = m_impl->majorRadius;
        minorRadius = m_impl->minorRadius;
    }

    double Ellipse::getRotation() const
    {
        return m_impl->rotation;
    }

    bool Ellipse::isCounterClockwise() const
    {
        return m_impl->ccw;
    }

    double Ellipse::getLength() const
    {
        return 0.0;
    }

    Ut::Rect2d& Ellipse::getRect()
    {
        Ut::Rect2d rect;
        for (auto pt : m_impl->vertices)
        {
            rect.expand(pt);
        }

        setRect(rect);
        return Entity::getRect();
    }

    void Ellipse::transform(const Ut::Mat3& matrix)
    {
        m_impl->center = matrix.transformPoint(m_impl->center);
        updateVertices();
    }

    Ut::Vec2d Ellipse::getValue(double t)
    {
        return getBasePoint();
    }

    double Ellipse::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}