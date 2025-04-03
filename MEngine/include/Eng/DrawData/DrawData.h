#ifndef DRAWDATA_H
#define DRAWDATA_H

#include <vector>
#include <memory>
#include "MEngineAPI.h"
#include "Scene/Group.h"

// 前向声明
class LineData;

namespace MEngine
{
    class MENGINE_API DrawData final
    {
    public:
        DrawData();
        ~DrawData();

    public:
        void processEntities(Group* group);

        float* getLineData(size_t& sz) const;
        std::pair<float*, size_t> getLineData() const;

    private:
        class Impl;
        Impl* pImpl; 
    };
}

#endif // DRAWDATA_H