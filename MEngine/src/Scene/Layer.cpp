#include "Scene/Layer/Layer.h"
#include "Entity/Entity.h"
#include <mutex>

namespace MEngine
{
    struct Layer::Impl
    {
        std::string m_name;
        std::vector<std::shared_ptr<Entity>> m_entities;
        int m_order;
        int m_color;
        bool m_active;
        bool m_locked;
        bool m_visible;
        bool m_processing;
        std::mutex m_mutex;
    };

    Layer::Layer(const std::string& name, int order, int color)
    {
        m_impl = new Impl();
        m_impl->m_name = name;
        m_impl->m_order = order;
        m_impl->m_color = color;
        m_impl->m_active = true;
        m_impl->m_locked = false;
        m_impl->m_visible = true;
        m_impl->m_processing = false;
    }

    Layer::~Layer()
    {
        delete m_impl;
    }

    void Layer::addEntity(std::shared_ptr<Entity> entity)
    {
        std::lock_guard<std::mutex> lock(m_impl->m_mutex);
        m_impl->m_entities.push_back(entity);
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

    const std::string& Layer::getName() const
    {
        return m_impl->m_name;
    }

    int Layer::getOrder() const
    {
        return m_impl->m_order;
    }

    int Layer::getColor() const
    {
        return m_impl->m_color;
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