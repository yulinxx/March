#include "Scene/Previews.h"
#include <set>
#include <algorithm>

namespace MEngine
{
    struct Previews::Impl
    {
        std::set<Entity*> m_setEntities; 
    };

    Previews::Previews()
    {
        m_pImpl = new Impl();
    }

    Previews::~Previews()
    {
        delete m_pImpl;
        m_pImpl = nullptr;
    }
    void Previews::addEntity(Entity* entity)
    {
        if (entity) {
            m_pImpl->m_setEntities.insert(entity);
        }
    }

    bool Previews::removeEntity(Entity* entity)
    {
        if (!entity) 
            return false;

        auto it = m_pImpl->m_setEntities.find(entity); 
        if (it != m_pImpl->m_setEntities.end())
        {
            m_pImpl->m_setEntities.erase(it);
            return true;
        }
        return false;
    }

    size_t Previews::getChildrenCount() const
    {
        return m_pImpl->m_setEntities.size();
    }
    
    Entity* Previews::getChild(size_t index) const
    {
        if (index >= m_pImpl->m_setEntities.size())
            return nullptr;
            
        auto it = m_pImpl->m_setEntities.begin();
        std::advance(it, index);  // 使用迭代器跳跃访问set元素
        return *it;
    }



    template<typename Func>
    void Previews::forEachEntity(Func&& func) const
    {
        for (const auto* entity : m_pImpl->m_setEntities)
        {
            func(entity);
        }
    }
}