#ifndef POINTDATA_H
#define POINTDATA_H

#include <vector>
#include "Entity/Point.h"

namespace MEngine
{
    struct PointData
    {
        void clear(); // 清空PointData中的数据，用于清除上一次的渲染数据

        // 收集Point数据的函数
        void collectPointData(const Point* point);

        // 将Point数据转换为适合渲染的浮点数组
        std::vector<float>& getPointData();

        std::vector<float> m_vPointPts;
    };
}
#endif // POINTDATA_H