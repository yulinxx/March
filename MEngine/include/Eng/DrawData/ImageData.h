#pragma once
#include <vector>
#include <memory>
#include "Entity/Image.h"

namespace MEngine
{
    class Image;

    class ImageData
    {
    public:
        ImageData();
        ~ImageData();

    public:
        void clear();
        void collectImageData(Image* image);
        
        std::pair<float*, size_t> getImageData() const;
        
    private:
        struct Impl;
        Impl* m_pImpl;
    };
}