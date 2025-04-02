#ifndef LINEDATA_H
#define LINEDATA_H

#include <vector>
#include "Entity/Line.h"

namespace MEngine
{
    struct LineData
    {
        void clear(); // 清空LineData中的数据，用于清除上一次的渲染数据

        // 收集Line数据的函数
        void collectLineData(Line* line);

        // 将Line数据转换为适合渲染的浮点数组
        std::vector<float>& getLineData();

        // 批量渲染相关方法，用于将多个LineData合并为一个大的渲染数据
        // static std::vector<float> batchRender(const std::vector<LineData>& lineDataList);

        std::vector<float> m_vLinePts;
    };
}
#endif // LINEDATA_H