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
        clear();
        delete pImpl;
    }

    void DrawData::clear()
    {
        clearPreviews();
        clearLineData();
        clearLinesData();
    }

    void DrawData::clearPreviews()
    {
        if (pImpl->m_previewData && !pImpl->m_previewData->m_vLinePts.empty())
        {
            pImpl->m_previewData->m_vLinePts.clear();
            pImpl->m_previewData->m_vLinePts.shrink_to_fit();
        }

        if (pImpl->m_previewsData && !pImpl->m_previewsData->m_vLinesPts.empty())
        {

            pImpl->m_previewsData->m_vLinesPts.clear();
            pImpl->m_previewsData->m_vLinesPts.shrink_to_fit();
        }
    }

    void DrawData::clearLineData()
    {
        if (pImpl->m_lineData && !pImpl->m_lineData->m_vLinePts.empty())
        {

            pImpl->m_lineData->m_vLinePts.clear();
            pImpl->m_lineData->m_vLinePts.shrink_to_fit();
        }
    }

    void DrawData::clearLinesData()
    {
        if (pImpl->m_linesData && !pImpl->m_linesData->m_vLinesPts.empty())
        {

            pImpl->m_linesData->m_vLinesPts.clear();
            pImpl->m_linesData->m_vLinesPts.shrink_to_fit();
        }
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
                switch (entity->getType())
                {
                case EntType::POINT:
                    // points.push_back(entity->m_basePt);
                    break;
                case EntType::LINE:
                {
                    auto line = static_cast<Line*>(entity);
                    pImpl->m_lineData->collectLineData(line);
                }
                break;
                case EntType::POLYGON:
                {
                    auto pg = static_cast<Polygon*>(entity);
                    pImpl->m_linesData->collectLinesData(pg);
                }
                break;
                case EntType::RECTANGLE:
                {
                    auto rect = static_cast<Rectangle*>(entity);
                    pImpl->m_linesData->collectLinesData(rect);
                }
                break;
                case EntType::ARC:
                {
                    auto arc = static_cast<Arc*>(entity);
                    pImpl->m_linesData->collectLinesData(arc);
                }
                break;
                case EntType::CIRCLE:
                {
                    auto cc = static_cast<Circle*>(entity);
                    pImpl->m_linesData->collectLinesData(cc);
                }
                break;
                case EntType::ELLIPSE:
                {
                    auto ellipse = static_cast<Ellipse*>(entity);
                    pImpl->m_linesData->collectLinesData(ellipse);
                }
                break;
                case EntType::LWPOLYLINE:
                {
                    auto pl = static_cast<PolyLine*>(entity);
                    pImpl->m_linesData->collectLinesData(pl);
                }
                break;
                case EntType::BSPLINE:
                {
                    auto sp = static_cast<CubicBSpline*>(entity);
                    pImpl->m_linesData->collectLinesData(sp);
                }
                break;
                case EntType::BEZIER:
                {
                    auto bz = static_cast<CubicBezier*>(entity);
                    pImpl->m_linesData->collectLinesData(bz);
                }
                break;
                case EntType::TEXT:
                    break;
                case EntType::UNKNOWN:
                    break;
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
                switch (entity->getType())
                {
                case EntType::POINT:
                    // points.push_back(entity->m_basePt);
                    break;
                case EntType::LINE:
                {
                    auto line = static_cast<Line*>(entity);
                    pImpl->m_previewData->collectLineData(line);
                }
                break;
                case EntType::POLYGON:
                {
                    auto pg = static_cast<Polygon*>(entity);
                    pImpl->m_previewsData->collectLinesData(pg);
                }
                break;
                case EntType::RECTANGLE:
                {
                    auto rect = static_cast<Rectangle*>(entity);
                    pImpl->m_previewsData->collectLinesData(rect);
                    break;
                }
                case EntType::ARC:
                {
                    auto arc = static_cast<Arc*>(entity);
                    pImpl->m_previewsData->collectLinesData(arc);
                }
                break;
                case EntType::CIRCLE:
                {
                    auto cc = static_cast<Circle*>(entity);
                    pImpl->m_previewsData->collectLinesData(cc);
                }
                break;
                case EntType::ELLIPSE:
                {
                    auto ellipse = static_cast<Ellipse*>(entity);
                    pImpl->m_previewsData->collectLinesData(ellipse);
                }
                break;
                case EntType::LWPOLYLINE:
                {
                    auto pl = static_cast<PolyLine*>(entity);
                    pImpl->m_previewsData->collectLinesData(pl);
                }
                break;
                case EntType::BSPLINE:
                {
                    auto sp = static_cast<CubicBSpline*>(entity);
                    pImpl->m_previewsData->collectLinesData(sp);
                }
                break;
                case EntType::BEZIER:
                {
                    auto bz = static_cast<CubicBezier*>(entity);
                    pImpl->m_previewsData->collectLinesData(bz);
                }
                break;
                case EntType::TEXT:
                    break;
                case EntType::UNKNOWN:
                    break;
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