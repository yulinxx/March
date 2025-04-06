#include "DrawData/LinesData.h"

namespace MEngine
{
    void LinesData::clear()
    {
        m_vLinesPts.clear();
        m_vLinesPts.shrink_to_fit();
    }

    // 收集Lines数据的函数实现
    void LinesData::collectLinesData(Polygon* pg)
    {
        std::pair<Ut::Vec2*, size_t> pairData = pg->getLinesData();
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