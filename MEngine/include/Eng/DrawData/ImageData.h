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

        size_t getImageDataSz() const;
        std::tuple<unsigned char*, int, int, int> getImageData(size_t n) const;

    private:
        struct Impl;
        Impl* m_pImpl;
    };
}