#include "Scene/OrderManager.h"

namespace MEngine
{
    // OrderManager::OrderManager() = default;
    // OrderManager::~OrderManager() = default;

    void OrderManager::addEntity(std::shared_ptr<Entity> entity)
    {
        if (m_mapEntIndex.find(entity) == m_mapEntIndex.end())
        {
            m_vOrderedEntities.push_back(entity);

            auto nIndex = m_vOrderedEntities.size() - 1;

            m_mapEntIndex[entity] = nIndex;
            entity->setId(nIndex);

            // 每次添加后按 m_nId 排序
            std::sort(m_vOrderedEntities.begin(), m_vOrderedEntities.end(), compareById);

            // 更新索引
            for (size_t i = 0; i < m_vOrderedEntities.size(); ++i)
            {
                auto& entity = m_vOrderedEntities[i];
                entity->setId(i);
                m_mapEntIndex[entity] = i;
            }
        }
    }

    void OrderManager::removeEntity(std::shared_ptr<Entity> entity)
    {
        auto it = m_mapEntIndex.find(entity);
        if (it != m_mapEntIndex.end())
        {
            size_t nIndex = it->second;

            // 移除指定元素
            m_vOrderedEntities.erase(m_vOrderedEntities.begin() + nIndex);

            // 更新后续元素的索引
            for (size_t i = nIndex; i < m_vOrderedEntities.size(); ++i)
            {
                auto& entity = m_vOrderedEntities[i];
                entity->setId(i);
                m_mapEntIndex[entity] = i;
            }
            // 从哈希表中移除该元素
            m_mapEntIndex.erase(it);
        }
    }

    std::vector<std::shared_ptr<Entity>>& OrderManager::getOrderedEntities()
    {
        // 返回按 m_nId 排序的图元列表
        return m_vOrderedEntities;
    }

    void OrderManager::swapEntities(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2)
    {
        auto it1 = m_mapEntIndex.find(entity1);
        auto it2 = m_mapEntIndex.find(entity2);
        if (it1 != m_mapEntIndex.end() && it2 != m_mapEntIndex.end())
        {
            size_t nIndex1 = it1->second;
            size_t nIndex2 = it2->second;

            auto& entity1 = m_vOrderedEntities[nIndex1];
            auto& entity2 = m_vOrderedEntities[nIndex2];

            // 交换向量中的元素
            std::swap(entity1, entity2);

            // 更新索引
            entity1->setId(nIndex2);
            entity2->setId(nIndex1);

            m_mapEntIndex[entity1] = nIndex2;
            m_mapEntIndex[entity2] = nIndex1;
        }
    }

    void OrderManager::moveEntityToPos(std::shared_ptr<Entity> entity, size_t position)
    {
        auto it = m_mapEntIndex.find(entity);
        if (it != m_mapEntIndex.end())
        {
            size_t currentIndex = it->second;
            if (currentIndex != position)
            {
                // 移除当前位置的元素
                m_vOrderedEntities.erase(m_vOrderedEntities.begin() + currentIndex);

                // 限制 position 到有效范围 [0, size()]
                size_t validPosition = std::min(position, m_vOrderedEntities.size());

                // 在指定位置插入元素
                m_vOrderedEntities.insert(m_vOrderedEntities.begin() + validPosition, entity);

                // 更新所有元素的索引
                for (size_t i = 0; i < m_vOrderedEntities.size(); ++i)
                {
                    auto& entity = m_vOrderedEntities[i];
                    entity->setId(i);
                    m_mapEntIndex[entity] = i;
                }
            }
        }
    }
}