#include "DrawData/PointData.h"

namespace MEngine
{
    void PointData::clear()
    {
    }

    void PointData::collectPointData(const Point* point)
    {
        vPt = point->getBasePoint();
    }

    // 将Point数据转换为适合渲染的浮点数组实现
    Ut::Vec2d& PointData::getPointData()
    {
        return vPt;
    }
}