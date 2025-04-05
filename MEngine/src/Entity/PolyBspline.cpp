#include "Entity/PolyBspline.h"

namespace MEngine
{
    PolyBspline::PolyBspline()
    {
        m_eType = EntType::SPLINE;
    }

    PolyBspline::~PolyBspline()
    {
    }

    std::pair<float*, size_t> PolyBspline::getLinesData() const
    {
        //return { pImpl->m_lineData->m_vLinePts.data(), 
        //    pImpl->m_lineData->m_vLinePts.size() };

        return {nullptr, 1};

    }

}