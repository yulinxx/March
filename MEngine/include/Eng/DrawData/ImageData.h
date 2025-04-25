#pragma once
#include <vector>
#include <memory>

namespace MEngine
{
    class Image;

    class ImageData
    {
    public:
        ImageData();
        ~ImageData();

        void clear();
        void collectImageData(Image* image);
        
        std::pair<float*, size_t> getImageData() const;
        
    private:
        struct Impl;
        Impl* pImpl;
    };
}