#include "DrawData/DrawData.h"
#include "DrawData/LineData.h"

#include "Scene/Group.h"
#include "Scene/Previews.h"

namespace MEngine
{
    class DrawData::Impl
    {
    public:
        std::unique_ptr<LineData> m_lineData{ nullptr };
        std::unique_ptr<LineData> m_previewData{ nullptr };
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


        for (size_t i = 0; i < group->getChildrenCount(); i++)
        {
            Entity* entity = group->getChild(i);
            if (entity)
            {
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


    void DrawData::processPreviews(Previews* previews)
    {
        if (!previews)
            return;

        if (!pImpl->m_previewData)
            pImpl->m_previewData = std::make_unique<LineData>();

        pImpl->m_previewData->clear();

        for (size_t i = 0; i < previews->getChildrenCount(); i++)
        {
            Entity* entity = previews->getChild(i);
            if (entity)
            {
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


    std::pair<float*, size_t> DrawData::getLineData() const
    {
        return { pImpl->m_lineData->m_vLinePts.data(), pImpl->m_lineData->m_vLinePts.size() };
    }

    std::pair<float*, size_t> DrawData::getPreviewData() const
    {
        return { pImpl->m_previewData->m_vLinePts.data(), pImpl->m_previewData->m_vLinePts.size() };
    }
}