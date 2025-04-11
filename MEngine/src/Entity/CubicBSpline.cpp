#include "Entity/CubicBSpline.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct CubicBSpline::Impl
    {
        std::vector<Ut::Vec2> controlPoints; // 控制点
        std::vector<double> knots;           // 节点向量
        size_t nSegmentsPerSpan = 32;        // 每段曲线的采样点数
        std::vector<Ut::Vec2> vertices;      // 顶点数据
    };

    CubicBSpline::CubicBSpline()
    {
        m_impl = new Impl();
        setType(EntType::BSPLINE);
        setClosed(false); // 默认不闭合
    }

    CubicBSpline::~CubicBSpline()
    {
        delete m_impl;
        m_impl = nullptr;
    }

    void CubicBSpline::clear()
    {
        m_impl->vertices.clear();
        m_impl->vertices.shrink_to_fit();
        m_impl->knots.clear();
        m_impl->controlPoints.clear();
    }

    void CubicBSpline::setControlPoints(const std::vector<Ut::Vec2>& points, bool closed)
    {
        if (points.size() < 4)
        {
            //throw std::runtime_error("Cubic B-Spline requires at least 4 control points");
            return;
        }

        clear();
        m_impl->controlPoints = points;
        isClosed();

        Entity::setClosed(closed);

        computeKnots();
        updateVertices();
    }

    void CubicBSpline::setSegmentsPerSpan(size_t nSegments)
    {
        if (nSegments < 2)
        {
            //throw std::runtime_error("Number of segments per span must be at least 2");
            return;
        }

        m_impl->nSegmentsPerSpan = nSegments;
        updateVertices();
    }

    void CubicBSpline::setClosed(bool closed)
    {
        Entity::setClosed(closed);
        computeKnots();
        updateVertices();
    }

    void CubicBSpline::computeKnots()
    {
        m_impl->knots.clear();
        if (m_impl->controlPoints.size() < 4)
            return; // 至少需要4个控制点

        int n = m_impl->controlPoints.size() - 1; // 控制点数 - 1
        int k = 3; // 三次 B 样条的阶数 (degree = k = 3)

        if (isClosed())
        {
            // 闭合曲线：均匀节点，额外添加控制点
            int totalKnots = n + k + 1 + k; // 额外添加 k 个节点
            for (int i = 0; i < totalKnots; ++i)
            {
                m_impl->knots.push_back(static_cast<double>(i) / (n + k + 1));
            }
            // 闭合时复制前 k 个控制点到末尾
            for (int i = 0; i < k && i < n; ++i) // 添加边界检查

            {
                m_impl->controlPoints.push_back(m_impl->controlPoints[i]);
            }
        }
        else
        {
            // 开合曲线：均匀节点，边界重复
            int totalKnots = n + k + 1;
            for (int i = 0; i < totalKnots; ++i)
            {
                double t = static_cast<double>(i) / (totalKnots - 1 - k);
                if (i < k + 1) t = 0.0;           // 前 k+1 个节点为 0
                else if (i >= n + 1) t = 1.0;     // 后 k 个节点为 1
                else t = static_cast<double>(i - k) / (n - k + 1);
                m_impl->knots.push_back(t);
            }
        }
    }

    double CubicBSpline::basisFunction(int i, int k, double t, const std::vector<double>& knots) const
    {
        // 检查基础情况和边界
        if (i < 0 || i >= static_cast<int>(knots.size()) || i + 1 >= static_cast<int>(knots.size()))
        {
            return 0.0;
        }
        if (k == 0)
        {
            return (t >= knots[i] && t < knots[i + 1]) ? 1.0 : 0.0;
        }

        double denom1 = knots[i + k] - knots[i];
        double denom2 = (i + k + 1 < static_cast<int>(knots.size())) ? knots[i + k + 1] - knots[i + 1] : 0.0;
        double b1 = 0.0, b2 = 0.0;

        // 只在 denom1 有效时计算 b1
        if (denom1 > 1e-6 && i + k < static_cast<int>(knots.size()))
        {
            b1 = (t - knots[i]) / denom1 * basisFunction(i, k - 1, t, knots);
        }
        // 只在 denom2 有效时计算 b2
        if (denom2 > 1e-6 && i + k + 1 < static_cast<int>(knots.size()))
        {
            b2 = (knots[i + k + 1] - t) / denom2 * basisFunction(i + 1, k - 1, t, knots);
        }

        return b1 + b2;
    }

    Ut::Vec2 CubicBSpline::evaluate(double t) const
    {
        if (t < 0.0 || t > 1.0)
        {
            throw std::runtime_error("Parameter t must be between 0 and 1");
        }

        if (m_impl->controlPoints.empty() || m_impl->knots.empty())
        {
            return Ut::Vec2(0.0, 0.0);
        }

        int n = m_impl->controlPoints.size() - 1;
        int k = 3; // 三次样条
        double tScaled = m_impl->knots[k] + t * (m_impl->knots[n + 1] - m_impl->knots[k]);

        Ut::Vec2 point(0.0, 0.0);
        for (int i = 0; i <= n; ++i)
        {
            double b = basisFunction(i, k, tScaled, m_impl->knots);
            point += m_impl->controlPoints[i] * b;
        }
        return point;
    }

    void CubicBSpline::updateVertices()
    {
        //clear();
        m_impl->vertices.clear();

        if (m_impl->controlPoints.size() < 4 || m_impl->nSegmentsPerSpan < 2)
        {
            return;
        }

        int n = isClosed() ? m_impl->controlPoints.size() - 3 : m_impl->controlPoints.size() - 3;
        size_t totalSegments = n * m_impl->nSegmentsPerSpan;

        for (size_t i = 0; i <= totalSegments; ++i)
        {
            double t = static_cast<double>(i) / totalSegments;
            Ut::Vec2 point = evaluate(t);
            m_impl->vertices.push_back(point);
        }
    }

    std::pair<Ut::Vec2*, size_t> CubicBSpline::getData() const
    {
        return { m_impl->vertices.data(), m_impl->vertices.size() };
    }

    std::vector<Ut::Vec2> CubicBSpline::getControlPoints() const
    {
        return m_impl->controlPoints;
    }

    double CubicBSpline::getLength() const
    {
        return 0.0;
    }

    Ut::Rect2d& CubicBSpline::getRect()
    {
        Ut::Rect2d rect;
        for (auto pt : m_impl->vertices)
        {
            rect.expand(pt);
        }

        setRect(rect);
        return Entity::getRect();
    }
    void CubicBSpline::transform(const Ut::Mat3& matrix)
    {
        
    }
    Ut::Vec2d CubicBSpline::getValue(double t)
    {
        return getBasePoint();
    }

    double CubicBSpline::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }
}