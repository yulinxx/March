#ifndef LINESDATA_H
#define LINESDATA_H

#include <vector>
#include "Entity/Polygon.h"

namespace MEngine
{
    struct LinesData
    {
        void clear();

        // 收集Line数据的函数
        void collectLinesData(Polygon* line);

        std::vector<float>& getLinesData();

        // 批量渲染相关方法，用于将多个LineData合并为一个大的渲染数据
        // static std::vector<float> batchRender(const std::vector<LineData>& lineDataList);

        std::vector<float> m_vLinesPts;
    };
}
#endif // LINESDATA_H