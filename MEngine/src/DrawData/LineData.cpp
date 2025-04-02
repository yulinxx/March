#include "DrawData/LineData.h"
namespace MEngine
{
    void LineData::clear() // 清空LineData中的数据，用于清除上一次的渲染数据
    {
        m_vLinePts.clear();
        m_vLinePts.shrink_to_fit();
    }

    // 收集Line数据的函数实现
    void LineData::collectLineData(Line* line)
    {
        m_vLinePts.push_back(static_cast<float>(line->m_basePt.x()));
        m_vLinePts.push_back(static_cast<float>(line->m_basePt.y()));
        //m_vLinePts.push_back(line->m_basePt.z);
        m_vLinePts.push_back(static_cast<float>(line->m_secPoint.x()));
        m_vLinePts.push_back(static_cast<float>(line->m_secPoint.y()));
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