#include "Entity/Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace MEngine
{
    struct Image::Impl
    {
        unsigned char* imgData = nullptr;   // 位图像素数据
        int width = 0;                      // 位图宽度
        int height = 0;                     // 位图高度
        int channels = 0;                   // 通道数

        Ut::Vec2 sz;                        // 显示大小

        Ut::Mat3 transform;                 // 变换矩阵
        std::vector<Ut::Vec2> vertices;     // 顶点数据（归一化）
        std::vector<Ut::Vec2> texCoords;    // 纹理坐标
        Ut::Rect2d rect;                    // 缓存的边界矩形

        Impl()
        {
        }
    };

    Image::Image() : m_impl(new Impl())
    {
        setType(EntType::IMAGE);

        m_impl->vertices = {
            Ut::Vec2(0.0, 0.0), Ut::Vec2(1.0, 0.0),
            Ut::Vec2(0.0, 1.0), Ut::Vec2(1.0, 1.0)
        };

        //m_impl->texCoords = {
        //    Ut::Vec2(0.0, 0.0), Ut::Vec2(1.0, 0.0),
        //    Ut::Vec2(0.0, 1.0), Ut::Vec2(1.0, 1.0)
        //};
    }

    Image::Image(const char* filePath) : Image()
    {
        loadFromFile(filePath);
    }

    Image::~Image()
    {
        if (m_impl->imgData)
            stbi_image_free(m_impl->imgData);

        delete m_impl;
    }

    void Image::clear()
    {
        if (m_impl->imgData)
        {
            stbi_image_free(m_impl->imgData);
            m_impl->imgData = nullptr;
        }

        m_impl->width = 0;
        m_impl->height = 0;
        m_impl->channels = 0;
        m_impl->sz = Ut::Vec2(0.0, 0.0);
        m_impl->transform = Ut::Mat3();
        m_impl->rect = Ut::Rect2d();

        setFlag(EntFlag::Dirty, true);
    }

    double Image::getLength() const
    {
        return  0.0;
    }

    Ut::Rect2d& Image::getRect()
    {
        return m_impl->rect;
        //auto rect = Ut::Rect2d(getBasePoint(), getBasePoint() + m_impl->sz);
        //setRect(rect);
        //return Entity::getRect();
    }

    void Image::transform(const Ut::Mat3& matrix)
    {
        //m_impl->transform = matrix * m_impl->transform;

        // 更新基准点
        Ut::Vec3d basePt(getBasePoint().x(), getBasePoint().y(), 1.0);
        basePt = matrix * basePt;
        setBasePoint(Ut::Vec2d(basePt.x(), basePt.y()));

        // 更新边界矩形
        std::vector<Ut::Vec2> transformedVertices = m_impl->vertices;
        for (auto& vertex : transformedVertices)
        {
            Ut::Vec3 v(vertex.x() * m_impl->sz.x(), vertex.y() * m_impl->sz.y(), 1.0);
            v = m_impl->transform * v;
            vertex = Ut::Vec2(v.x(), v.y());
        }

        double minX = transformedVertices[0].x(), maxX = minX;
        double minY = transformedVertices[0].y(), maxY = minY;

        for (const auto& v : transformedVertices)
        {
            minX = std::min(minX, v.x());
            maxX = std::max(maxX, v.x());
            minY = std::min(minY, v.y());
            maxY = std::max(maxY, v.y());
        }
        m_impl->rect = Ut::Rect2d(Ut::Vec2d(minX, minY), Ut::Vec2d(maxX, maxY));

        setFlag(EntFlag::Dirty, true);

        //Entity::transform(matrix);
    }

    std::pair<Ut::Vec2*, size_t> Image::getData() const
    {
        // static std::vector<Ut::Vec2> vertexData(4);
        // for (size_t i = 0; i < 4; ++i)
        // {
        //     Ut::Vec3 v(m_impl->vertices[i].x() * m_impl->sz.x(),
        //         m_impl->vertices[i].y() * m_impl->sz.y(), 1.0);

        //     v = m_impl->transform * v;
        //     vertexData[i] = Ut::Vec2(v.x(), v.y());
        // }

        // return { vertexData.data(), vertexData.size() };

        return { nullptr, 0 };
    }

    Ut::Vec2d Image::getValue(double t)
    {
        return getBasePoint();
    }

    double Image::EvalParam(const Ut::Vec2& p)
    {
        return 0.0;
    }

    void Image::loadFromFile(const char* filePath)
    {
        if (m_impl->imgData)
        {
            stbi_image_free(m_impl->imgData);
            m_impl->imgData = nullptr;
        }

        m_impl->imgData = stbi_load(filePath,
            &m_impl->width,
            &m_impl->height,
            &m_impl->channels,
            0);

        if (m_impl->imgData)
        {
            m_impl->sz = Ut::Vec2(static_cast<double>(m_impl->width), static_cast<double>(m_impl->height));
            m_impl->rect = Ut::Rect2d(getBasePoint(), getBasePoint() + m_impl->sz);
            setFlag(EntFlag::Dirty, true);
        }
    }

    void Image::setPosition(const Ut::Vec2& pos)
    {
        Entity::setBasePoint(pos);

        m_impl->rect = Ut::Rect2d(getBasePoint(), getBasePoint() + m_impl->sz);
        setFlag(EntFlag::Dirty, true);
    }

    void Image::setSize(const Ut::Vec2& sz)
    {
        m_impl->sz = sz;
        m_impl->rect = Ut::Rect2d(getBasePoint(), getBasePoint() + m_impl->sz);
        setFlag(EntFlag::Dirty, true);
    }

    Ut::Vec2 Image::getSize() const
    {
        return m_impl->sz;
    }

    unsigned char* Image::getImageData() const
    {
        return m_impl->imgData;
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

    // const std::vector<Ut::Vec2>& Image::getTexCoords() const
    // {
    //     return m_impl->texCoords;
    // }

    // const Ut::Mat3& Image::getTransform() const
    // {
    //     return m_impl->transform;
    // }
}