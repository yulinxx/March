#ifndef LINESDATA_H
#define LINESDATA_H

#include <vector>
#include "Entity/Point.h"
#include "Entity/Line.h"
#include "Entity/PolyLine.h"
#include "Entity/Polygon.h"
#include "Entity/Rectangle.h"
#include "Entity/Arc.h"
#include "Entity/Circle.h"
#include "Entity/Ellipse.h"
#include "Entity/CubicBezier.h"
#include "Entity/CubicBSpline.h"

namespace MEngine
{
    struct LinesData
    {
        void clear();

        // 收集Line数据的函数
        void collectLinesData(PolyLine* pl);
        void collectLinesData(Polygon* polygon);
        void collectLinesData(Rectangle* rect);
        void collectLinesData(Arc* arc);
        void collectLinesData(Circle* circle);
        void collectLinesData(Ellipse* ellipse);
        void collectLinesData(CubicBezier* bezier);
        void collectLinesData(CubicBSpline* bsPline);

        std::vector<float>& getLinesData();

        // 批量渲染相关方法，用于将多个LineData合并为一个大的渲染数据
        // static std::vector<float> batchRender(const std::vector<LineData>& lineDataList);

        std::vector<float> m_vLinesPts;
    };
}
#endif // LINESDATA_H