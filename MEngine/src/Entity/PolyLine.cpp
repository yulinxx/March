#include "Entity/PolyLine.h"
#include <stdexcept>

namespace MEngine
{
    PolyLine::PolyLine()
    {
        m_eType = ETYPE::LWPOLYLINE;
    }
    PolyLine::~PolyLine()
    {
    }

    // Vec2 PolyLine::getValue(double t)
    // {
    //     if (t < 0 || t > 1)
    //         throw std::runtime_error("t out of range");
    //     if (m_bReverse)
    //         t = 1 - t;

    //     t *= entitylist.size() - 1;
    //     int n = static_cast<int>(t);
    //     double tt = t - n;
    //     return entitylist[n]->getValue(tt);
    // }

    // double PolyLine::EvalParam(const Ut::Vec2 &p)
    // {
    //     return 0;
    //     // double t;
    //     // double min_d = 1e+20;

    //     // for (auto &item : entitylist)
    //     // {
    //     //     auto t1 = item->EvalParam(p);
    //     //     auto d = (item->getValue(t1) - p).norm();
    //     //     if (d < min_d)
    //     //     {
    //     //         min_d = d;
    //     //         t = t1;
    //     //     }
    //     // }

    //     // if (m_bReverse)
    //     // {
    //     //     return 1 - t;
    //     // }
    //     // return t;
    // }
}