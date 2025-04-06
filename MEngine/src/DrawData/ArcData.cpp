#include "DrawData/ArcData.h"

namespace MEngine
{
    void ArcData::clear() // 清空ArcData中的数据，用于清除上一次的渲染数据
    {
        m_vArcPts.clear();
        m_vArcPts.shrink_to_fit();
    }

    // 收集Arc数据的函数实现
    void ArcData::collectArcData(const Arc* arc)
    {
        //m_vArcPts.push_back(static_cast<float>(arc->m_basePt.x()));
        //m_vArcPts.push_back(static_cast<float>(arc->m_basePt.y()));
        //m_vArcPts.push_back(arc->m_basePt.z);
    }

    // 将Arc数据转换为适合渲染的浮点数组实现
    std::vector<float>& ArcData::getArcData()
    {
        return m_vArcPts;
    }
}