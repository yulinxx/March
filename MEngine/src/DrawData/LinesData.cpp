#include "DrawData/LinesData.h"

namespace MEngine
{
    void LinesData::clear()
    {
        m_vLinesPts.clear();
        m_vLinesPts.shrink_to_fit();

        m_vIndex.clear();
        m_vIndex.shrink_to_fit();
    }

    // 收集Lines数据的函数实现

    void LinesData::collectLinesData(PolyLine* pl)
    {
        return collectEntLinesData(pl);

        std::pair<Ut::Vec2*, size_t> pairData = pl->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Polygon* polygon)
    {
        return collectEntLinesData(polygon);

        std::pair<Ut::Vec2*, size_t> pairData = polygon->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Rectangle* rect)
    {
        return collectEntLinesData(rect);

        std::pair<Ut::Vec2*, size_t> pairData = rect->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
            m_vLinesPts.push_back(0.0f);
            if (rect->getFlag(EntFlag::Select))
            {
                m_vLinesPts.push_back(1.0f);
                m_vLinesPts.push_back(0.0f);
                m_vLinesPts.push_back(0.0f);
            }
            else
            {
                m_vLinesPts.push_back(0.0f);
                m_vLinesPts.push_back(1.0f);
                m_vLinesPts.push_back(0.0f);
            }
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Arc* arc)
    {
        return collectEntLinesData(arc);

        std::pair<Ut::Vec2*, size_t> pairData = arc->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
            m_vLinesPts.push_back(0.0f);
            if (arc->getFlag(EntFlag::Select))
            {
                m_vLinesPts.push_back(1.0f);
                m_vLinesPts.push_back(0.0f);
                m_vLinesPts.push_back(0.0f);
            }
            else
            {
                m_vLinesPts.push_back(0.0f);
                m_vLinesPts.push_back(1.0f);
                m_vLinesPts.push_back(0.0f);
            }
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Circle* circle)
    {
        return collectEntLinesData(circle);

        std::pair<Ut::Vec2*, size_t> pairData = circle->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
            m_vLinesPts.push_back(0.0f);
            if (circle->getFlag(EntFlag::Select))
            {
                m_vLinesPts.push_back(1.0f);
                m_vLinesPts.push_back(0.0f);
                m_vLinesPts.push_back(0.0f);
            }
            else
            {
                m_vLinesPts.push_back(0.0f);
                m_vLinesPts.push_back(1.0f);
                m_vLinesPts.push_back(0.0f);
            }
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(Ellipse* ellipse)
    {
        return collectEntLinesData(ellipse);

        std::pair<Ut::Vec2*, size_t> pairData = ellipse->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(CubicBezier* bezier)
    {
        return collectEntLinesData(bezier);

        std::pair<Ut::Vec2*, size_t> pairData = bezier->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectLinesData(CubicBSpline* bsPline)
    {
        return collectEntLinesData(bsPline);

        std::pair<Ut::Vec2*, size_t> pairData = bsPline->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
        }

        
        constexpr float nan = std::numeric_limits<float>::quiet_NaN();
        m_vLinesPts.push_back(nan);
        m_vLinesPts.push_back(nan);
    }

    void LinesData::collectEntLinesData(Entity* ent)
    {
        std::pair<Ut::Vec2*, size_t> pairData = ent->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        // 当前顶点数据的起始索引
        unsigned int baseIndex = static_cast<unsigned int>(m_vLinesPts.size() / 6);

        // 遍历图元的所有顶点
        for (size_t i = 0; i < sz; i++)
        {
            // 添加位置 (xyz)
            m_vLinesPts.push_back(static_cast<float>(pts[i].x()));
            m_vLinesPts.push_back(static_cast<float>(pts[i].y()));
            m_vLinesPts.push_back(0.0f); // z 固定为 0

            // 根据选择状态添加颜色 (rgb)
            if (ent->getFlag(EntFlag::Select))
            {
                m_vLinesPts.push_back(1.0f); // r
                m_vLinesPts.push_back(0.0f); // g
                m_vLinesPts.push_back(0.0f); // b
            }
            else
            {
                m_vLinesPts.push_back(0.0f); // r
                m_vLinesPts.push_back(1.0f); // g
                m_vLinesPts.push_back(0.0f); // b
            }
            m_vIndex.push_back(baseIndex + i);
        }

        constexpr unsigned int restartIndex = std::numeric_limits<unsigned int>::max();
        m_vIndex.push_back(restartIndex);
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