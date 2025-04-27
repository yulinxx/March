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

    size_t ImageData::getImageDataSz() const
    {
        return m_pImpl->vImageData.size();
    }

    std::tuple<unsigned char*, int, int, int> ImageData::getImageData(size_t n) const
    {
        if (n >= m_pImpl->vImageData.size() || n < 0)
            return { nullptr, 0, 0, 0 };

        return { m_pImpl->vImageData[n].data, m_pImpl->vImageData[n].width,
                m_pImpl->vImageData[n].height, m_pImpl->vImageData[n].channels };
    }
}