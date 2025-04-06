#include "Entity/CubicBSpline.h"
#include <stdexcept>
#include <cmath>

namespace MEngine
{
    struct CubicBSpline::Impl
    {
        std::vector<Ut::Vec2> controlPoints; // ���Ƶ�
        std::vector<double> knots;           // �ڵ�����
        size_t nSegmentsPerSpan = 32;        // ÿ�����ߵĲ�������
        // bool closed = false;                 // �Ƿ�պ�
        std::vector<Ut::Vec2> vertices;      // ��������
    };

    CubicBSpline::CubicBSpline()
    {
        m_impl = new Impl();
        setType(EntType::BSPLINE);
        setClosed(false);
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
    }

    void CubicBSpline::setControlPoints(const std::vector<Ut::Vec2>& points, bool closed)
    {
        if (points.size() < 4)
        {
            throw std::runtime_error("Cubic B-Spline requires at least 4 control points");
        }

        clear();
        m_impl->controlPoints = points;
        // m_impl->closed = closed;

        setClosed(closed);
        computeKnots();
        updateVertices();
    }

    void CubicBSpline::setSegmentsPerSpan(size_t nSegments)
    {
        if (nSegments < 2)
        {
            throw std::runtime_error("Number of segments per span must be at least 2");
        }
        m_impl->nSegmentsPerSpan = nSegments;
        updateVertices();
    }

    void CubicBSpline::setClosed(bool closed)
    {
        // m_impl->closed = closed;
        // m_bClosed = closed;
        setClosed(closed);
        computeKnots();
        updateVertices();
    }

    void CubicBSpline::computeKnots()
    {
        m_impl->knots.clear();
        size_t n = m_impl->controlPoints.size() - 1; // ���Ƶ��� - 1
        size_t k = 3; // ���� B �����Ľ��� (degree = k = 3)

        if (isClosed())
        {
            // �պ����ߣ����Ƚڵ㣬������ӿ��Ƶ�
            int totalKnots = n + k + 1 + k; // ������� k ���ڵ�
            for (int i = 0; i < totalKnots; ++i)
            {
                m_impl->knots.push_back(static_cast<double>(i) / (n + k + 1));
            }
            // �պ�ʱ����ǰ k �����Ƶ㵽ĩβ
            for (int i = 0; i < k; ++i)
            {
                m_impl->controlPoints.push_back(m_impl->controlPoints[i]);
            }
        }
        else
        {
            // �������ߣ����Ƚڵ㣬�߽��ظ�
            int totalKnots = n + k + 1;
            for (int i = 0; i < totalKnots; ++i)
            {
                double t = static_cast<double>(i) / (totalKnots - 1 - k);
                if (i < k + 1)
                    t = 0.0;           // ǰ k+1 ���ڵ�Ϊ 0
                else if (i >= n + 1) t = 1.0;     // �� k ���ڵ�Ϊ 1
                else t = static_cast<double>(i - k) / (n - k + 1);
                m_impl->knots.push_back(t);
            }
        }
    }

    double CubicBSpline::basisFunction(int i, int k, double t, const std::vector<double>& knots) const
    {
        if (k == 0)
        {
            return (t >= knots[i] && t < knots[i + 1]) ? 1.0 : 0.0;
        }

        double denom1 = knots[i + k] - knots[i];
        double denom2 = knots[i + k + 1] - knots[i + 1];
        double b1 = 0.0, b2 = 0.0;

        if (denom1 > 1e-6)
        {
            b1 = (t - knots[i]) / denom1 * basisFunction(i, k - 1, t, knots);
        }
        if (denom2 > 1e-6)
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
        if (m_impl->controlPoints.empty())
        {
            return Ut::Vec2(0.0, 0.0);
        }

        int n = m_impl->controlPoints.size() - 1;
        size_t k = 3; // ��������
        double tScaled = m_impl->knots[k] + t * (m_impl->knots[n + 1] - m_impl->knots[k]);

        Ut::Vec2 point(0.0, 0.0);
        for (size_t i = 0; i <= n; ++i)
        {
            double b = basisFunction(i, k, tScaled, m_impl->knots);
            point += m_impl->controlPoints[i] * b;
        }
        return point;
    }

    void CubicBSpline::updateVertices()
    {
        clear();

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
}