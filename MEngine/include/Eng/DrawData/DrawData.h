#ifndef DRAWDATA_H
#define DRAWDATA_H

#include <vector>
#include <tuple>
#include <memory>
#include "MEngineAPI.h"

namespace MEngine
{
    struct LineData;
    class Group;
    class Previews;

    class MENGINE_API DrawData final
    {
    public:
        DrawData();
        ~DrawData();

    public:
        void clear();
        void clearPreviews();

        void clearLinesData();
        void clearLineData();

    public:
        void processEntities(Group* group);
        void processPreviews(Previews* previews);

    public:
        // 直线段
        std::pair<float*, size_t> getLineData() const;
        std::pair<float*, size_t> getPreviewData() const;

        // 多线段
        std::pair<float*, size_t> getLinesData() const;
        std::pair<unsigned int*, size_t> getLinesIndex() const;

        std::pair<float*, size_t> getPreviewsData() const;
        std::pair<unsigned int*, size_t> getPreviewsIndex() const;

        std::tuple<unsigned char*, int, int, int> getImageData() const;

    private:
        class Impl;
        Impl* pImpl;
    };
}

#endif // DRAWDATA_H