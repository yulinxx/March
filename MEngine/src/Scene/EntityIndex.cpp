#include "Scene/EntityIndex.h"
#include <algorithm>
#include <unordered_set>

namespace MEngine
{
    EntityIndex::EntityIndex() : m_entTree()
    {
    }

    void EntityIndex::addEntity(std::shared_ptr<Entity> entity)
    {
        if (entity)
        {
            m_entTree.insert(std::make_pair(entity->getRect(), entity));
        }
    }

    void EntityIndex::removeEntity(std::shared_ptr<Entity> entity)
    {
        if (entity)
        {
            m_entTree.remove(std::make_pair(entity->getRect(), entity));
        }
    }

    // 查询给定矩形区域内的所有实体 - 完全包含在矩形内的实体
    std::vector<std::shared_ptr<Entity>> EntityIndex::getEntities(const Ut::Rect2d& rect) const
    {
        std::vector<RTreeRectEnt> results;
        m_entTree.query(bgi::contains(rect), std::back_inserter(results));

        std::vector<std::shared_ptr<Entity>> entities;
        for (const auto& pair : results)
        {
            entities.push_back(pair.second);
        }
        return entities;
    }

    // 交选实现 - 与矩形相交的实体
    std::vector<std::shared_ptr<Entity>> EntityIndex::getCrossEntities(const Ut::Rect2d& rect) const
    {
        std::vector<RTreeRectEnt> results;
        m_entTree.query(bgi::intersects(rect), std::back_inserter(results));

        std::vector<std::shared_ptr<Entity>> entities;
        entities.reserve(results.size());

        for (const auto& result : results)
        {
            entities.push_back(result.second);
        }

        return entities;
    }

    // 反选实现 - 不在矩形内的实体
    std::vector<std::shared_ptr<Entity>> EntityIndex::getInverseSelectedEntities(const Ut::Rect2d& rect) const
    {
        auto all = getAllEntities();
        auto selected = getCrossEntities(rect);

        // 使用set提高查找效率
        std::unordered_set<std::shared_ptr<Entity>> selectedSet(selected.begin(), selected.end());

        std::vector<std::shared_ptr<Entity>> result;
        for (const auto& entity : all)
        {
            if (selectedSet.find(entity) == selectedSet.end())
            {
                result.push_back(entity);
            }
        }
        return result;
    }

    // 查询距离某点最近的 k 个实体
    std::vector<std::shared_ptr<Entity>> EntityIndex::getNearestEntities(const Ut::Vec2d& point, size_t k) const
    {
        std::vector<RTreeRectEnt> results;
        m_entTree.query(bgi::nearest(point, k), std::back_inserter(results));

        std::vector<std::shared_ptr<Entity>> entities;
        entities.reserve(results.size());

        for (const auto& result : results)
        {
            entities.push_back(result.second);
        }

        return entities;
    }

    Ut::Rect2d EntityIndex::getBoundingBox() const
    {
        if (m_entTree.empty())
        {
            return Ut::Rect2d();
        }
        auto bound = m_entTree.bounds();

        return Ut::Rect2d(
            Ut::Vec2d(bound.min_corner().get<0>(), bound.min_corner().get<1>()),
            Ut::Vec2d(bound.max_corner().get<0>(), bound.max_corner().get<1>())
        );
    }

    std::vector<std::shared_ptr<Entity>> EntityIndex::getAllEntities() const
    {
        //std::vector<RTreeRectEnt> results;
        //m_entTree.query(bgi::intersects(Ut::Rect2d(Ut::Point(-DBL_MAX, -DBL_MAX), Ut::Point(DBL_MAX, DBL_MAX))),
        //    std::back_inserter(results));
        //std::vector<std::shared_ptr<Entity>> entities;
        //entities.reserve(results.size());
        //for (const auto& result : results)
        //{
        //    entities.push_back(result.second);
        //}
        //return entities;

        std::vector<RTreeRectEnt> results;
        m_entTree.query(bgi::intersects(m_entTree.bounds()), std::back_inserter(results));

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