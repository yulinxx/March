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
        Ut::Vec2 startPoint;
        Ut::Vec2 endPoint;
        line->getPoints(startPoint, endPoint);
        m_vLinePts.push_back(static_cast<float>(startPoint.x()));
        m_vLinePts.push_back(static_cast<float>(startPoint.y()));
        //m_vLinePts.push_back(line->m_basePt.z);
        m_vLinePts.push_back(static_cast<float>(endPoint.x()));
        m_vLinePts.push_back(static_cast<float>(endPoint.y()));
        //m_vLinePts.push_back(line->m_secPoint.z);
    }

    // 将Line数据转换为适合渲染的浮点数组实现
    std::vector<float>& LineData::getLineData()
    {
        return m_vLinePts;
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