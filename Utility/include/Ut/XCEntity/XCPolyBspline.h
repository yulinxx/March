#ifndef XCPOLYBSPLINE_H
#define XCPOLYBSPLINE_H

#include "XCEntity.h"
#include "../UtilityAPI.h"
#include <Eigen/Eigen>

namespace XC
{
    struct UTILITY_API XCPolyBspline : public XCEntity
    {
        int nDegree;    // B样条曲线的阶数

        double* pKnots; // 节点向量
        int knotSize;   // 节点向量大小

        double* pWeights; // 权重向量
        int weightSize; // 权重向量大小

        Ut::Vec2d* pControlPts; // 控制点向量
        int controlPtsSize; // 控制点向量大小

        // /**
        //  * @brief B样条曲线的阶数，决定曲线的平滑度和灵活性。
        //  */
        // int nDegree;
        // /**
        //  * @brief 节点向量，定义B样条基函数的分段区间。
        //  */
        // std::vector<double> vKnots;
        // /**
        //  * @brief 权重向量，每个控制点对应一个权重，影响曲线形状。
        //  */
        // std::vector<double> vWeights;
        // /**
        //  * @brief 控制点向量，定义B样条曲线的大致形状。
        //  */
        // std::vector<Ut::Vec2d> vControlPts;
        XCPolyBspline();
        ~XCPolyBspline();
    };
}

#endif // XCPOLYBSPLINE_H