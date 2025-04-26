#include "DrawData/ImageData.h"
#include "Entity/Image.h"

namespace MEngine
{
    struct ImageData::Impl
    {
        struct ImageData
        {
            unsigned char* data;
            int width;
            int height;
            int channels;
        };

        std::vector<ImageData> vImageData;
    };

    ImageData::ImageData() : m_pImpl(new Impl())
    {
    }

    ImageData::~ImageData()
    {
        delete m_pImpl;
    }

    void ImageData::clear()
    {
        //m_pImpl->textureIDs.clear();
        //m_pImpl->vertexData.clear();
        //m_pImpl->uvData.clear();
        //m_pImpl->transforms.clear();
    }

    void ImageData::collectImageData(Image* image)
    {
        if (!image)
            return;

        Impl::ImageData imgData;
        imgData.data = image->getImageData();
        imgData.width = image->getWidth();
        imgData.height = image->getHeight();
        imgData.channels = image->getChannels();

        m_pImpl->vImageData.emplace_back(imgData);
    }

    std::pair<float*, size_t> ImageData::getImageData() const
    {
        //return {m_pImpl->vertexData.data(), m_pImpl->vertexData.size()};
        // return { m_pImpl->m_vImagePts.data(), m_pImpl->m_vImagePts.size() };
        return { nullptr, 0 };
    }
}