#ifndef CIRCLEDATA_H
#define CIRCLEDATA_H

#include <vector>
#include "Entity/Circle.h"

namespace MEngine
{
    struct CircleData
    {
        void clear();

        // 收集Circle数据的函数
        void collectCircleData(const Circle* circle);

        // 将Circle数据转换为适合渲染的浮点数组
        std::vector<float>& getCircleData();

        std::vector<float> m_vCirclePts;
    };
}
#endif // CIRCLEDATA_H