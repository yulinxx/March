#include "DrawData/PointData.h"
namespace MEngine
{
    void PointData::clear() // 清空PointData中的数据，用于清除上一次的渲染数据
    {
        m_vPointPts.clear();
        m_vPointPts.shrink_to_fit();
    }

    // 收集Point数据的函数实现
    void PointData::collectPointData(const Point* point)
    {
        m_vPointPts.push_back(static_cast<float>(point->m_basePt.x()));
        m_vPointPts.push_back(static_cast<float>(point->m_basePt.y()));
        //m_vPointPts.push_back(point->m_basePt.z);
    }

    // 将Point数据转换为适合渲染的浮点数组实现
    std::vector<float>& PointData::getPointData()
    {
        return m_vPointPts;
    }
}