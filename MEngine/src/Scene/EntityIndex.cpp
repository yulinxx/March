#include "Scene/EntityIndex.h"
#include <algorithm>

namespace MEngine
{
    EntityIndex::EntityIndex() : m_entTree()
    {
    }

    void EntityIndex::insert(std::shared_ptr<Entity> entity, const Ut::Rect2d& box)
    {
        if (entity)
        {
            m_entTree.insert(std::make_pair(box, entity));
        }
    }

    void EntityIndex::insert(Entity* entity, const Ut::Rect2d& box)
    {
        if (entity)
        {
            m_entTree.insert(std::make_pair(box, std::shared_ptr<Entity>(entity, [](Entity*) {}))); // 不释放原始指针
        }
    }

    void EntityIndex::insertBatch(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities)
    {
        for (const auto& [entity, box] : entities)
        {
            if (entity)
            {
                m_entTree.insert(std::make_pair(box, entity));
            }
        }
    }

    bool EntityIndex::remove(const std::shared_ptr<Entity>& entity, const Ut::Rect2d& box)
    {
        if (entity)
        {
            return m_entTree.remove(std::make_pair(box, entity)) > 0;
        }
        return false;
    }

    bool EntityIndex::remove(Entity* entity, const Ut::Rect2d& box)
    {
        if (entity)
        {
            return m_entTree.remove(std::make_pair(box, std::shared_ptr<Entity>(entity, [](Entity*) {}))) > 0;
        }
        return false;
    }

    size_t EntityIndex::removeBatch(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities)
    {
        size_t count = 0;
        for (const auto& [entity, box] : entities)
        {
            if (entity && m_entTree.remove(std::make_pair(box, entity)) > 0)
            {
                ++count;
            }
        }
        return count;
    }

    std::vector<std::shared_ptr<Entity>> EntityIndex::queryIntersects(const Ut::Rect2d& queryBox) const
    {
        std::vector<RTreeValue> results;
        m_entTree.query(bgi::intersects(queryBox), std::back_inserter(results));
        std::vector<std::shared_ptr<Entity>> entities;
        entities.reserve(results.size());
        for (const auto& result : results)
        {
            entities.push_back(result.second);
        }
        return entities;
    }

    std::vector<std::shared_ptr<Entity>> EntityIndex::queryContains(const Ut::Point& point) const
    {
        std::vector<RTreeValue> results;
        m_entTree.query(bgi::contains(point), std::back_inserter(results));
        std::vector<std::shared_ptr<Entity>> entities;
        entities.reserve(results.size());
        for (const auto& result : results)
        {
            entities.push_back(result.second);
        }
        return entities;
    }

    std::vector<std::shared_ptr<Entity>> EntityIndex::queryNearest(const Ut::Point& point, size_t k) const
    {
        std::vector<RTreeValue> results;
        m_entTree.query(bgi::nearest(point, k), std::back_inserter(results));
        std::vector<std::shared_ptr<Entity>> entities;
        entities.reserve(results.size());
        for (const auto& result : results)
        {
            entities.push_back(result.second);
        }
        return entities;
    }

    std::vector<std::shared_ptr<Entity>> EntityIndex::getAllEntities() const
    {
        std::vector<RTreeValue> results;
        m_entTree.query(bgi::intersects(Ut::Rect2d(Ut::Point(-DBL_MAX, -DBL_MAX), Ut::Point(DBL_MAX, DBL_MAX))),
            std::back_inserter(results));
        std::vector<std::shared_ptr<Entity>> entities;
        entities.reserve(results.size());
        for (const auto& result : results)
        {
            entities.push_back(result.second);
        }
        return entities;
    }

    void EntityIndex::clear()
    {
        m_entTree.clear();
    }

    size_t EntityIndex::size() const
    {
        return m_entTree.size();
    }

    bool EntityIndex::empty() const
    {
        return m_entTree.empty();
    }
} // namespace MEngine