#include "DrawData/ImageData.h"
#include "Entity/Image.h"

namespace MEngine
{
    struct ImageData::Impl
    {
        std::vector<float> m_vImagePts; // 存储位置、大小和纹理坐标等信息
    };

    ImageData::ImageData() : pImpl(new Impl()) {}
    ImageData::~ImageData() { delete pImpl; }

    void ImageData::clear()
    {
        pImpl->m_vImagePts.clear();
        pImpl->m_vImagePts.shrink_to_fit();
    }

    void ImageData::collectImageData(Image* image)
    {
        if (!image) return;
        
        // 获取图像位置和大小
        auto pos = image->getBasePoint();
        auto size = image->getSize();
        
        // 添加图像数据到集合中
        // 格式: [x, y, width, height, texCoordX, texCoordY, ...]
        pImpl->m_vImagePts.push_back(static_cast<float>(pos.x()));
        pImpl->m_vImagePts.push_back(static_cast<float>(pos.y()));
        pImpl->m_vImagePts.push_back(static_cast<float>(size.x()));
        pImpl->m_vImagePts.push_back(static_cast<float>(size.y()));
        
        // 添加纹理坐标 (这里使用默认全图)
        pImpl->m_vImagePts.push_back(0.0f); // texCoord left
        pImpl->m_vImagePts.push_back(0.0f); // texCoord bottom
        pImpl->m_vImagePts.push_back(1.0f); // texCoord right
        pImpl->m_vImagePts.push_back(1.0f); // texCoord top
    }

    std::pair<float*, size_t> ImageData::getImageData() const
    {
        return { pImpl->m_vImagePts.data(), pImpl->m_vImagePts.size() };
    }
}