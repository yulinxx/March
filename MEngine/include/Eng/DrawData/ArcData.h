#ifndef ARCDATA_H
#define ARCDATA_H

#include <vector>
#include "Entity/Arc.h"

namespace MEngine
{
    struct ArcData
    {
        void clear(); // 清空ArcData中的数据，用于清除上一次的渲染数据

        // 收集Arc数据的函数
        void collectArcData(const Arc* arc);

        // 将Arc数据转换为适合渲染的浮点数组
        std::vector<float>& getArcData();

        std::vector<float> m_vArcPts;
    };
}
#endif // ARCDATA_H