#include "DrawData/DrawData.h"
#include "DrawData/LineData.h"
#include "DrawData/LinesData.h"

#include "Scene/Group.h"
#include "Scene/Previews.h"

namespace MEngine
{
    class DrawData::Impl
    {
    public:
        std::unique_ptr<LineData> m_lineData{ nullptr };
        std::unique_ptr<LinesData> m_linesData{ nullptr };
        std::unique_ptr<LineData> m_previewData{ nullptr };
        std::unique_ptr<LinesData> m_previewsData{ nullptr };
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

        if (!pImpl->m_linesData)
            pImpl->m_linesData = std::make_unique<LinesData>();

        pImpl->m_linesData->clear();

        for (size_t i = 0; i < group->getChildrenCount(); i++)
        {
            Entity* entity = group->getChild(i);
            if (entity)
            {
                switch (entity->m_eType)
                {
                case EntType::POINT:
                    // points.push_back(entity->m_basePt);
                    break;
                case EntType::LINE:
                {
                    auto line = static_cast<Line*>(entity);
                    pImpl->m_lineData->collectLineData(line);
                    break;
                }
                case EntType::POLYGON:
                {
                    auto pg = static_cast<Polygon*>(entity);
                    pImpl->m_linesData->collectLinesData(pg);
                    break;
                }
                //case EntType::ARC:
                //    arcs.push_back(entity);
                //    break;
                //case EntType::CIRCLE:
                //    circles.push_back(entity);
                //    break;
                //case EntType::LWPOLYLINE:
                //    lwpolylines.push_back(entity);
                //    break;
                //case EntType::SPLINE:
                //    splines.push_back(entity);
                //    break;
                //case EntType::TEXT:
                //    texts.push_back(entity);
                //    break;
                //case EntType::UNKNOWN:
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

        if (!pImpl->m_previewsData)
            pImpl->m_previewsData = std::make_unique<LinesData>();

        pImpl->m_previewsData->clear();

        for (size_t i = 0; i < previews->getChildrenCount(); i++)
        {
            Entity* entity = previews->getChild(i);
            if (entity)
            {
                switch (entity->m_eType)
                {
                case EntType::POINT:
                    // points.push_back(entity->m_basePt);
                    break;
                case EntType::LINE:
                {
                    auto line = static_cast<Line*>(entity);
                    pImpl->m_lineData->collectLineData(line);
                    break;
                }
                case EntType::POLYGON:
                {
                    auto pg = static_cast<Polygon*>(entity);
                    pImpl->m_linesData->collectLinesData(pg);
                    break;
                }
                //case EntType::ARC:
                //    arcs.push_back(entity);
                //    break;
                //case EntType::CIRCLE:
                //    circles.push_back(entity);
                //    break;
                //case EntType::LWPOLYLINE:
                //    lwpolylines.push_back(entity);
                //    break;
                //case EntType::SPLINE:
                //    splines.push_back(entity);
                //    break;
                //case EntType::TEXT:
                //    texts.push_back(entity);
                //    break;
                //case EntType::UNKNOWN:
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
        return { pImpl->m_lineData->m_vLinePts.data(),
            pImpl->m_lineData->m_vLinePts.size() };
    }

    std::pair<float*, size_t> DrawData::getLinesData() const
    {
        return { pImpl->m_linesData->m_vLinesPts.data(),
            pImpl->m_linesData->m_vLinesPts.size() };
    }

    std::pair<float*, size_t> DrawData::getPreviewData() const
    {
        return { pImpl->m_previewData->m_vLinePts.data(),
            pImpl->m_previewData->m_vLinePts.size() };
    }

    std::pair<float*, size_t> DrawData::getPreviewsData() const
    {
        return { pImpl->m_previewsData->m_vLinesPts.data(),
            pImpl->m_previewsData->m_vLinesPts.size() };
    }
}