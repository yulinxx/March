#include "Entity/Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace MEngine
{
    struct Image::Impl
    {
        unsigned char* pixelData = nullptr;
        int width = 0;
        int height = 0;
        int channels = 0;
        Ut::Vec2 size;
    };

    Image::Image() : m_impl(new Impl())
    {
        setType(EntType::IMAGE);
    }

    Image::Image(const char* filePath) : Image()
    {
        loadFromFile(filePath);
    }

    Image::~Image()
    {
        if (m_impl->pixelData)
            stbi_image_free(m_impl->pixelData);

        delete m_impl;
    }

    void Image::clear()
    {

    }

    double Image::getLength() const
    {
        return  0.0;
    }

    Ut::Rect2d& Image::getRect()
    {
        auto rect = Ut::Rect2d(getBasePoint(), getBasePoint() + m_impl->size);
        setRect(rect);
        return Entity::getRect();
    }

    void Image::transform(const Ut::Mat3& matrix)
    {
        //Entity::transform(matrix);
    }

    std::pair<Ut::Vec2*, size_t> Image::getData() const
    {
        return { nullptr, 0 };
    }

    Ut::Vec2d Image::getValue(double t)
    {
        return  { 0.0, 0.0 };
    }

    double Image::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }


    void Image::loadFromFile(const char* filePath)
    {
        if (m_impl->pixelData)
        {
            stbi_image_free(m_impl->pixelData);
            m_impl->pixelData = nullptr;
        }

        m_impl->pixelData = stbi_load(filePath,
            &m_impl->width,
            &m_impl->height,
            &m_impl->channels,
            0);

        if (m_impl->pixelData)
        {
            m_impl->size = Ut::Vec2(m_impl->width, m_impl->height);
        }
    }

    void Image::setSize(const Ut::Vec2& size)
    {
        m_impl->size = size;
    }

    Ut::Vec2 Image::getSize() const
    {
        return m_impl->size;
    }

    unsigned char* Image::getPixelData() const
    {
        return m_impl->pixelData;
    }

    int Image::getWidth() const
    {
        return m_impl->width;
    }

    int Image::getHeight() const
    {
        return m_impl->height;
    }

    int Image::getChannels() const
    {
        return m_impl->channels;
    }


}