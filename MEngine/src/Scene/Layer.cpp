#include "Scene/Layer/Layer.h"
#include "Entity/Entity.h"
#include <mutex>

namespace MEngine
{
    struct Layer::Impl
    {
        std::string m_name = "";
        std::vector<std::shared_ptr<Entity>> m_entities;
        int m_order = 0;
        int m_color = 0xFF000000;
        float m_depth = 0.0f;
        bool m_active = true;
        bool m_locked = false;
        bool m_visible = true;
        bool m_processing = false;
        std::mutex m_mutex;
    };

    Layer::Layer()
    {
        m_impl = new Impl();

        init();
    }

    Layer::Layer(const char* name, int order, int color)
    {
        m_impl = new Impl();
        m_impl->m_name = name ? name : "";
        m_impl->m_order = order;
        m_impl->m_color = color;

        init();
    }

    Layer::~Layer()
    {
        delete m_impl;
    }

    void Layer::init()
    {
    }

    void Layer::addEntity(std::shared_ptr<Entity> entity)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        m_impl->m_entities.push_back(entity);
    }

    // 添加批量图元（使用 std::shared_ptr）
    void Layer::addEntities(const std::vector<std::shared_ptr<Entity>>& entities)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        m_impl->m_entities.insert(m_impl->m_entities.end(), entities.begin(), entities.end());
    }

    // 添加普通指针图元
    void Layer::addEntity(Entity* entity)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        m_impl->m_entities.push_back(std::shared_ptr<Entity>(entity));
    }

    // 添加普通指针批量图元
    void Layer::addEntities(const std::vector<Entity*>& entities)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        for (auto entity : entities)
        {
            m_impl->m_entities.push_back(std::shared_ptr<Entity>(entity));
        }
    }

    void Layer::removeEntity(std::shared_ptr<Entity> entity)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        auto& entities = m_impl->m_entities;
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            if (*it == entity)
            {
                entities.erase(it);
                break;
            }
        }
    }

    // 删除批量图元（使用 std::shared_ptr）
    void Layer::removeEntities(const std::vector<std::shared_ptr<Entity>>& entities)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        for (auto entity : entities)
        {
            auto& vecEntities = m_impl->m_entities;
            for (auto it = vecEntities.begin(); it != vecEntities.end(); ++it)
            {
                if (*it == entity)
                {
                    vecEntities.erase(it);
                    break;
                }
            }
        }
    }

    // 删除普通指针图元
    void Layer::removeEntity(Entity* entity)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        auto& entities = m_impl->m_entities;
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            if (it->get() == entity)
            {
                entities.erase(it);
                break;
            }
        }
    }

    // 删除普通指针批量图元
    void Layer::removeEntities(const std::vector<Entity*>& entities)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        for (auto entity : entities)
        {
            auto& vecEntities = m_impl->m_entities;
            for (auto it = vecEntities.begin(); it != vecEntities.end(); ++it)
            {
                if (it->get() == entity)
                {
                    vecEntities.erase(it);
                    break;
                }
            }
        }
    }

    void Layer::setLocked(bool locked)
    {
        m_impl->m_locked = locked;
    }

    void Layer::setVisible(bool visible)
    {
        m_impl->m_visible = visible;
    }

    void Layer::setProcessing(bool processing)
    {
        m_impl->m_processing = processing;
    }

    const char* Layer::getName() const
    {
        return m_impl->m_name.c_str();
    }

    int Layer::getOrder() const
    {
        return m_impl->m_order;
    }

    //int Layer::setColor(int color)
    //{
    //    //unsigned char a = (color >> 24) & 0xFF; // 透明度
    //    //unsigned char r = (color >> 16) & 0xFF; // 红
    //    //unsigned char g = (color >> 8) & 0xFF; // 绿
    //    //unsigned char b = color & 0xFF;         // 蓝

    //    //void receiveColor(unsigned char* colorData)
    //    //{
    //    //    unsigned char r = colorData[0];
    //    //    unsigned char g = colorData[1];
    //    //    unsigned char b = colorData[2];
    //    //    unsigned char a = colorData[3];

    //    //    // 使用颜色，例如 OpenGL
    //    //    glColor4ub(r, g, b, a);
    //    //}

    //    m_impl->m_color = color;
    //}

    // 设置颜色（整数形式）
    int Layer::setColor(int color)
    {
        m_impl->m_color = color; // 直接赋值，假设调用者提供正确格式 (0xAARRGGBB)
        return 0; // 返回 0 表示成功
    }

    // 设置颜色（RGBA 字节形式）
    int Layer::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        m_impl->m_color = (a << 24) | (r << 16) | (g << 8) | b; // 构造 0xAARRGGBB
        return 0; // 返回 0 表示成功
    }

    // 获取颜色（整数形式）
    int Layer::getColor() const
    {
        return m_impl->m_color;
    }

    // 获取颜色（RGBA 字节形式）
    void Layer::getColor(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a) const
    {
        if (r) *r = (m_impl->m_color >> 16) & 0xFF; // 红
        if (g) *g = (m_impl->m_color >> 8) & 0xFF;  // 绿
        if (b) *b = m_impl->m_color & 0xFF;         // 蓝
        if (a) *a = (m_impl->m_color >> 24) & 0xFF; // 透明度
    }

    bool Layer::isActive() const
    {
        return m_impl->m_active;
    }

    bool Layer::isLocked() const
    {
        return m_impl->m_locked;
    }

    bool Layer::isVisible() const
    {
        return m_impl->m_visible;
    }

    bool Layer::isProcessing() const
    {
        return m_impl->m_processing;
    }
}