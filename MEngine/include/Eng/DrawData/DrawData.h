#ifndef DRAWDATA_H
#define DRAWDATA_H

#include <vector>
#include <memory>
#include "MEngineAPI.h"
#include "Scene/Group.h"
#include "DrawData/LineData.h"

namespace MEngine
{
    class MENGINE_API DrawData final
    {
    public:
        DrawData() = default;

    public:
        void processEntities(Group* group);

    private:
        std::unique_ptr<LineData> m_lineData{ nullptr };
    };
}

#endif // DRAWDATA_H