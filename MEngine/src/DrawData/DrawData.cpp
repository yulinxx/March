#include "DrawData/DrawData.h"
#include "DrawData/LineData.h"

namespace MEngine
{
    class DrawData::Impl
    {
    public:
        std::unique_ptr<LineData> m_lineData{ nullptr };
    };

    DrawData::DrawData()
    {
        pImpl = new Impl();
    }

    DrawData::~DrawData()
    {
        delete pImpl;
    }

    void DrawData::processEntities(Group* group)

    {
        if (!group)
            return;

        if (!pImpl->m_lineData)
            pImpl->m_lineData = std::make_unique<LineData>();

        pImpl->m_lineData->clear();

        // auto collectData = [&](Entity* entity) {
        //     switch (entity->m_eType) {
        //     case ETYPE::POINT:
        //         // points.push_back(entity->m_basePt);
        //         break;
        //     case ETYPE::LINE:
        //     {
        //         Line* line = static_cast<Line*>(entity);
        //         m_lineData->collectLineData(line);
        //         break;
        //     }
        //     //case ETYPE::ARC:
        //     //    arcs.push_back(entity);
        //     //    break;
        //     //case ETYPE::CIRCLE:
        //     //    circles.push_back(entity);
        //     //    break;
        //     //case ETYPE::LWPOLYLINE:
        //     //    lwpolylines.push_back(entity);
        //     //    break;
        //     //case ETYPE::SPLINE:
        //     //    splines.push_back(entity);
        //     //    break;
        //     //case ETYPE::TEXT:
        //     //    texts.push_back(entity);
        //     //    break;
        //     //case ETYPE::UNKNOWN:
        //     //    unknowns.push_back(entity);
        //     //    break;
        //     default:
        //         break;
        //     }
        // };

        // group->forEachEntity(collectData);

        for (size_t i = 0; i < group->getChildrenCount(); ++i)
        {
            Entity* entity = group->getChild(i);
            if (entity)
            { // 检查指针是否有效
                switch (entity->m_eType)
                {
                case ETYPE::POINT:
                    // points.push_back(entity->m_basePt);
                    break;
                case ETYPE::LINE:
                {
                    auto line = static_cast<Line*>(entity);
                    pImpl->m_lineData->collectLineData(line);
                    break;
                }
                //case ETYPE::ARC:
                //    arcs.push_back(entity);
                //    break;
                //case ETYPE::CIRCLE:
                //    circles.push_back(entity);
                //    break;
                //case ETYPE::LWPOLYLINE:
                //    lwpolylines.push_back(entity);
                //    break;
                //case ETYPE::SPLINE:
                //    splines.push_back(entity);
                //    break;
                //case ETYPE::TEXT:
                //    texts.push_back(entity);
                //    break;
                //case ETYPE::UNKNOWN:
                //    unknowns.push_back(entity);
                //    break;
                default:
                    break;
                }
            }
        }
    }


    float* DrawData::getLineData(size_t& sz) const
    {
        if (nullptr == pImpl->m_lineData)
            return nullptr;

        sz = pImpl->m_lineData->m_vLinePts.size();
        return pImpl->m_lineData->m_vLinePts.data();
    }

    std::pair<float*, size_t> DrawData::getLineData() const
    {
        return { pImpl->m_lineData->m_vLinePts.data(), pImpl->m_lineData->m_vLinePts.size() };
    }
}