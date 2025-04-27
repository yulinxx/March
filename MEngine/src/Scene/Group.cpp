#include "Scene/Group.h"
#include <algorithm>

namespace MEngine
{
    struct Group::Impl
    {
        std::vector<std::shared_ptr<Entity>> m_vecEntities;
    };

    Group::Group()
    {
        m_pImpl = new Impl();
    }

    Group::~Group()
    {
        delete m_pImpl;
        m_pImpl = nullptr;
    }

    void Group::addEntity(std::shared_ptr<Entity> entity)
    {
        m_pImpl->m_vecEntities.push_back(entity);
    }

    void Group::removeEntity(std::shared_ptr<Entity> entity)
    {
        if (!entity)
            return;

        auto it = std::find(m_pImpl->m_vecEntities.begin(), m_pImpl->m_vecEntities.end(), entity);
        if (it != m_pImpl->m_vecEntities.end())
        {
            m_pImpl->m_vecEntities.erase(it);
            return;
        }
    }

    size_t Group::getChildrenCount() const
    {
        return m_pImpl->m_vecEntities.size();
    }

    Entity* Group::getChild(size_t index) const
    {
        return (index < m_pImpl->m_vecEntities.size()) ? m_pImpl->m_vecEntities[index].get() : nullptr;
    }

    template<typename Func>
    void Group::forEachEntity(Func&& func) const
    {
        for (const auto* entity : m_pImpl->m_vecEntities)
        {
            func(entity);
        }
    }
}