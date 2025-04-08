#include "Scene/EntityIndex.h"
#include <algorithm>

namespace MEngine
{
    EntityIndex::EntityIndex() : m_entTree()
    {
    }

    void EntityIndex::addEntity(Entity* entity)
    {
        if (entity)
        {
            m_entTree.insert(std::make_pair(entity->getRect(),
                std::shared_ptr<Entity>(entity, [](Entity*) {})));
        }
    }

    void EntityIndex::addEntity(std::shared_ptr<Entity> entity)
    {
        if (entity)
        {
            m_entTree.insert(std::make_pair(entity->getRect(), entity));
        }
    }

    void EntityIndex::addEntity(Entity* entity, const Ut::Rect2d& box)
    {
        if (entity)
        {
            m_entTree.insert(std::make_pair(box,
                std::shared_ptr<Entity>(entity, [](Entity*) {})));
        }
    }

    void EntityIndex::addEntity(const std::vector<Entity*>& entities)
    {

        for (const auto& entity : entities)
        {
            addEntity(entity);
        }
    }

    void EntityIndex::addEntity(const std::vector<std::shared_ptr<Entity>>& entities)
    {
        for (const auto& entity : entities)
        {
            if (entity)
            {
                addEntity(entity);
            }
        }
    }



    void EntityIndex::removeEntity(Entity* entity)
    {
        if (entity)
        {
            m_entTree.remove(std::make_pair(entity->getRect(),
                std::shared_ptr<Entity>(entity, [](Entity*) {})));
        }
    }

    void EntityIndex::removeEntity(std::shared_ptr<Entity> entity)
    {
        if (entity)
        {
            m_entTree.remove(std::make_pair(entity->getRect(), entity));
        }
    }

    void EntityIndex::removeEntity(Entity* entity, const Ut::Rect2d& box)
    {
        if (entity)
        {
            m_entTree.remove(std::make_pair(box,
                std::shared_ptr<Entity>(entity, [](Entity*) {})));
        }
    }

    void EntityIndex::removeEntity(const std::vector<Entity*>& entities)
    {

        for (const auto& entity : entities)
        {
            removeEntity(entity);
        }
    }

    void EntityIndex::removeEntity(const std::vector<std::shared_ptr<Entity>>& entities)
    {
        for (const auto& entity : entities)
        {
            if (entity)
            {
                removeEntity(entity);
            }
        }
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