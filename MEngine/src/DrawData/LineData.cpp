#include "DrawData/LineData.h"
namespace MEngine
{
    void LineData::clear()
    {
        m_vLinePts.clear();
        m_vLinePts.shrink_to_fit();
    }

    // 收集Line数据的函数实现
    void LineData::collectLineData(Line* line)
    {
        //Ut::Vec2 startPoint;
        //Ut::Vec2 endPoint;
        //line->getPoints(startPoint, endPoint);
        //m_vLinePts.push_back(static_cast<float>(startPoint.x()));
        //m_vLinePts.push_back(static_cast<float>(startPoint.y()));
        ////m_vLinePts.push_back(line->m_basePt.z);
        //m_vLinePts.push_back(static_cast<float>(endPoint.x()));
        //m_vLinePts.push_back(static_cast<float>(endPoint.y()));
        ////m_vLinePts.push_back(line->m_secPoint.z);

        std::pair<Ut::Vec2*, size_t> pairData = line->getData();
        Ut::Vec2* pts = pairData.first;
        size_t sz = pairData.second;

        for (size_t i = 0; i < sz; i++)
        {
            m_vLinePts.push_back(static_cast<float>(pts[i].x()));
            m_vLinePts.push_back(static_cast<float>(pts[i].y()));
            m_vLinePts.push_back(0.0f);

            if (line->getFlag(EntFlag::Select))
            {
                m_vLinePts.push_back(1.0f); // r
                m_vLinePts.push_back(0.0f); // g
                m_vLinePts.push_back(0.0f); // b
            }
            else
            {
                unsigned char r, g, b, a;
                line->getLayerColor(&r, &g, &b, &a);
                m_vLinePts.push_back(static_cast<float>(r) / 255.0f);
                m_vLinePts.push_back(static_cast<float>(g) / 255.0f);
                m_vLinePts.push_back(static_cast<float>(b) / 255.0f);
            }
        }
    }

    // 批量渲染相关方法实现
    // std::vector<float> LineData::batchRender(const std::vector<LineData>& lineDataList) {
    //     std::vector<float> allLineData;
    //     for (const auto& lineData : lineDataList) {
    //         auto singleLineData = lineData.getLineData();
    //         allLineData.insert(allLineData.end(), singleLineData.begin(), singleLineData.end());
    //     }
    //     return allLineData;
    // }
}