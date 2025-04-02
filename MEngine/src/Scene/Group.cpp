#include "Scene/Group.h"
#include <vector>
#include <algorithm>

namespace MEngine
{
    struct Group::Impl
    {
        std::vector<Entity*> m_vecEntities;
    };

    Group::Group() : m_pImpl(std::make_unique<Impl>())
    {
    }

    Group::~Group() = default;

    void Group::addEntity(Entity* entity)
    {
        if (entity && std::find(m_pImpl->m_vecEntities.begin(), m_pImpl->m_vecEntities.end(), entity) == m_pImpl->m_vecEntities.end())
        {
            m_pImpl->m_vecEntities.push_back(entity);
        }
    }

    bool Group::removeEntity(Entity* entity)
    {
        if (!entity) return false;
        auto it = std::find(m_pImpl->m_vecEntities.begin(), m_pImpl->m_vecEntities.end(), entity);
        if (it != m_pImpl->m_vecEntities.end())
        {
            m_pImpl->m_vecEntities.erase(it);
            return true;
        }
        return false;
    }

    size_t Group::getChildrenCount() const
    {
        return m_pImpl->m_vecEntities.size();
    }

    Entity* Group::getChild(size_t index) const
    {
        return (index < m_pImpl->m_vecEntities.size()) ? m_pImpl->m_vecEntities[index] : nullptr;
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