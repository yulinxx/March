#include "DrawData/LinesData.h"

namespace MEngine
{
    void LinesData::clear()
    {
        m_vLinesPts.clear();
        m_vLinesPts.shrink_to_fit();
    }

    // 收集Lines数据的函数实现

    void LinesData::collectLinesData(PolyLine* pl)
    {
        std::pair<Ut::Vec2*, size_t> pairData = pl->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Polygon* polygon)
    {
        std::pair<Ut::Vec2*, size_t> pairData = polygon->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Rectangle* rect)
    {
        std::pair<Ut::Vec2*, size_t> pairData = rect->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Arc* arc)
    {
        std::pair<Ut::Vec2*, size_t> pairData = arc->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Circle* circle)
    {
        std::pair<Ut::Vec2*, size_t> pairData = circle->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Ellipse* ellipse)
    {
        std::pair<Ut::Vec2*, size_t> pairData = ellipse->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(CubicBezier* bezier)
    {
        std::pair<Ut::Vec2*, size_t> pairData = bezier->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(CubicBSpline* bsPline)
    {
        std::pair<Ut::Vec2*, size_t> pairData = bsPline->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        // 添加分隔符（IEEE NaN值）
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    // 将Line数据转换为适合渲染的浮点数组实现
    std::vector<float>& LinesData::getLinesData()
    {
        return m_vLinesPts;
    }

    // 批量渲染相关方法实现
    // std::vector<float> LinesData::batchRender(const std::vector<LinesData>& lineDataList) {
    //     std::vector<float> allLineData;
    //     for (const auto& lineData : lineDataList) {
    //         auto singleLineData = lineData.getLineData();
    //         allLineData.insert(allLineData.end(), singleLineData.begin(), singleLineData.end());
    //     }
    //     return allLineData;
    // }
}