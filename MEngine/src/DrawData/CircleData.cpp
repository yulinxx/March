#include "DrawData/CircleData.h"
namespace MEngine
{
    void CircleData::clear() // 清空CircleData中的数据，用于清除上一次的渲染数据
    {
        m_vCirclePts.clear();
        m_vCirclePts.shrink_to_fit();
    }

    // 收集Circle数据的函数实现
    void CircleData::collectCircleData(const Circle* circle)
    {
        //m_vCirclePts.push_back(float(circle->m_basePt.x()));
        //m_vCirclePts.push_back(float(circle->m_basePt.y()));
        //m_vCirclePts.push_back(circle->m_basePt.z);
    }

    // 将Circle数据转换为适合渲染的浮点数组实现
    std::vector<float>& CircleData::getCircleData()
    {
        return m_vCirclePts;
    }
}