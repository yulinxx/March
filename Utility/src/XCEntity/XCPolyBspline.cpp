#include "XCEntity/XCPolyBspline.h"

#include "tools.h"

namespace XC
{
    XCPolyBspline::XCPolyBspline()
        : nDegree(0), pKnots(nullptr), knotSize(0),
        pWeights(nullptr), weightSize(0),
        pControlPts(nullptr), controlPtsSize(0)
    {
    }

    XCPolyBspline::~XCPolyBspline()
    {
        SAFE_DEL(pKnots);
        SAFE_DEL(pWeights);
        SAFE_DEL(pControlPts);
    }
}