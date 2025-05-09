#include "DrawData/DrawData.h"
#include "DrawData/LineData.h"
#include "DrawData/LinesData.h"
#include "DrawData/ImageData.h"

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

        std::unique_ptr<ImageData> m_imageData{ nullptr };
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

        size_t sz = group->getChildrenCount();
        if (sz < 1)
            return;

        if (!pImpl->m_lineData)
            pImpl->m_lineData = std::make_unique<LineData>();

        if (!pImpl->m_linesData)
            pImpl->m_linesData = std::make_unique<LinesData>();

        if (!pImpl->m_imageData)
            pImpl->m_imageData = std::make_unique<ImageData>();

        pImpl->m_lineData->clear();
        pImpl->m_linesData->clear();
        pImpl->m_imageData->clear();

        for (size_t i = 0; i < sz; i++)
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
                    pImpl->m_linesData->collectEntLinesData(pg);
                }
                break;
                case EntType::RECTANGLE:
                {
                    auto rect = static_cast<Rectangle*>(entity);
                    pImpl->m_linesData->collectEntLinesData(rect);
                }
                break;
                case EntType::ARC:
                {
                    auto arc = static_cast<Arc*>(entity);
                    pImpl->m_linesData->collectEntLinesData(arc);
                }
                break;
                case EntType::CIRCLE:
                {
                    auto cc = static_cast<Circle*>(entity);
                    pImpl->m_linesData->collectEntLinesData(cc);
                }
                break;
                case EntType::ELLIPSE:
                {
                    auto ellipse = static_cast<Ellipse*>(entity);
                    pImpl->m_linesData->collectEntLinesData(ellipse);
                }
                break;
                case EntType::LWPOLYLINE:
                {
                    auto pl = static_cast<PolyLine*>(entity);
                    pImpl->m_linesData->collectEntLinesData(pl);
                }
                break;
                case EntType::BSPLINE:
                {
                    auto sp = static_cast<CubicBSpline*>(entity);
                    pImpl->m_linesData->collectEntLinesData(sp);
                }
                break;
                case EntType::BEZIER:
                {
                    auto bz = static_cast<CubicBezier*>(entity);
                    pImpl->m_linesData->collectEntLinesData(bz);
                }
                break;
                case EntType::TEXT:
                    break;
                case EntType::IMAGE:
                {
                    auto image = static_cast<Image*>(entity);
                    pImpl->m_imageData->collectImageData(image);
                }
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
                    pImpl->m_previewsData->collectEntLinesData(pg);
                }
                break;
                case EntType::RECTANGLE:
                {
                    auto rect = static_cast<Rectangle*>(entity);
                    pImpl->m_previewsData->collectEntLinesData(rect);
                    break;
                }
                case EntType::ARC:
                {
                    auto arc = static_cast<Arc*>(entity);
                    pImpl->m_previewsData->collectEntLinesData(arc);
                }
                break;
                case EntType::CIRCLE:
                {
                    auto cc = static_cast<Circle*>(entity);
                    pImpl->m_previewsData->collectEntLinesData(cc);
                }
                break;
                case EntType::ELLIPSE:
                {
                    auto ellipse = static_cast<Ellipse*>(entity);
                    pImpl->m_previewsData->collectEntLinesData(ellipse);
                }
                break;
                case EntType::LWPOLYLINE:
                {
                    auto pl = static_cast<PolyLine*>(entity);
                    pImpl->m_previewsData->collectEntLinesData(pl);
                }
                break;
                case EntType::BSPLINE:
                {
                    auto sp = static_cast<CubicBSpline*>(entity);
                    pImpl->m_previewsData->collectEntLinesData(sp);
                }
                break;
                case EntType::BEZIER:
                {
                    auto bz = static_cast<CubicBezier*>(entity);
                    pImpl->m_previewsData->collectEntLinesData(bz);
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
        if (!pImpl->m_lineData || pImpl->m_lineData->m_vLinePts.empty())
            return { nullptr, 0 };
        else
            return { pImpl->m_lineData->m_vLinePts.data(),
                pImpl->m_lineData->m_vLinePts.size() };
    }

    std::pair<float*, size_t> DrawData::getPreviewData() const
    {
        if (!pImpl->m_previewData || pImpl->m_previewData->m_vLinePts.empty())
            return { nullptr, 0 };
        else
            return { pImpl->m_previewData->m_vLinePts.data(),
                pImpl->m_previewData->m_vLinePts.size() };
    }

    std::pair<float*, size_t> DrawData::getLinesData() const
    {
        if (!pImpl->m_linesData || pImpl->m_linesData->m_vLinesPts.empty())
            return { nullptr, 0 };
        else
            return { pImpl->m_linesData->m_vLinesPts.data(),
                pImpl->m_linesData->m_vLinesPts.size() };
    }

    std::pair<unsigned int*, size_t> DrawData::getLinesIndex() const
    {
        if (!pImpl->m_linesData || pImpl->m_linesData->m_vIndex.empty())
            return { nullptr, 0 };
        else
            return { pImpl->m_linesData->m_vIndex.data(),
                pImpl->m_linesData->m_vIndex.size() };
    }

    std::pair<float*, size_t> DrawData::getPreviewsData() const
    {
        if (!pImpl->m_previewsData || pImpl->m_previewsData->m_vLinesPts.empty())
            return { nullptr, 0 };
        else
            return { pImpl->m_previewsData->m_vLinesPts.data(),
                pImpl->m_previewsData->m_vLinesPts.size() };
    }

    std::pair<unsigned int*, size_t> DrawData::getPreviewsIndex() const
    {
        if (!pImpl->m_previewsData || pImpl->m_previewsData->m_vIndex.empty())
            return { nullptr, 0 };
        else
            return { pImpl->m_previewsData->m_vIndex.data(),
                pImpl->m_previewsData->m_vIndex.size() };
    }

    // std::pair<float*, size_t> DrawData::getImageData() const
    // {
    //     return pImpl->m_imageData->getImageData();
    // }

    std::tuple<unsigned char*, int, int, int> DrawData::getImageData() const
    {
        if (!pImpl->m_imageData || pImpl->m_imageData->getImageDataSz() < 1)
            return { nullptr, 0, 0, 0 };
        else
            return pImpl->m_imageData->getImageData(0);
    }
}