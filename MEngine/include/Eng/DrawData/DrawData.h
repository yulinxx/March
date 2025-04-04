#ifndef DRAWDATA_H
#define DRAWDATA_H

#include <vector>
#include <memory>
#include "MEngineAPI.h"



namespace MEngine
{
    class LineData;
    class Group;
    class Previews;

    class MENGINE_API DrawData final
    {
    public:
        DrawData();
        ~DrawData();

    public:
        void processEntities(Group* group);
        void processPreviews(Previews* previews);

        std::pair<float*, size_t> getLineData() const;
        std::pair<float*, size_t> getPreviewData() const;

    private:
        class Impl;
        Impl* pImpl;
    };
}

#endif // DRAWDATA_H