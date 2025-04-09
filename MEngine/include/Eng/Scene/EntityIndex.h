#ifndef ENTITYINDEX_H
#define ENTITYINDEX_H

#include "IndexDef.h"

using namespace Ut;
namespace MEngine
{
    using RTreeRectEnt = std::pair<Ut::Rect2d, std::shared_ptr<Entity>>;
    using EntRTree = bgi::rtree<RTreeRectEnt, bgi::quadratic<16>>;

    class MENGINE_API EntityIndex
    {
    public:
        EntityIndex();

    public:
        // 插入
        void addEntity(Entity* entity);
        void addEntity(std::shared_ptr<Entity> entity);
        void addEntity(Entity* entity, const Ut::Rect2d& box);

        void addEntity(const std::vector<Entity*>& entities);
        void addEntity(const std::vector<std::shared_ptr<Entity>>& entities);

        // 删除
        void removeEntity(Entity* entity);
        void removeEntity(std::shared_ptr<Entity> entity);
        void removeEntity(Entity* entity, const Ut::Rect2d& box);

        void removeEntity(const std::vector<Entity*>& entities);
        void removeEntity(const std::vector<std::shared_ptr<Entity>>& entities);


        // 查询函数
        std::vector<std::shared_ptr<Entity>> query(const Ut::Rect2d& region) const;
        std::vector<std::shared_ptr<Entity>> queryPoint(const Ut::Vec2d& point) const;
        std::vector<std::shared_ptr<Entity>> queryNearest(const Ut::Vec2d& point, size_t k = 1) const;
        std::vector<std::shared_ptr<Entity>> queryIntersects(const Ut::Rect2d& region) const;

        // 获取所有图元
        std::vector<std::shared_ptr<Entity>> getAllEntities() const;

        void clear();

        size_t size() const;

        bool empty() const;

    private:
        EntRTree m_entTree;
    };
} // namespace MEngine

#endif // ENTITYINDEX_H

/*

#include "EntityIndex.h"
#include "PointEntity.h"
#include <iostream>

int main() {
    MEngine::EntityIndex spatialIndex;

    // 创建图元
    auto p1 = std::make_shared<MEngine::PointEntity>(1.0, 1.0);
    auto p2 = std::make_shared<MEngine::PointEntity>(2.0, 2.0);
    auto p3 = std::make_shared<MEngine::PointEntity>(3.0, 3.0);

    // 插入单个图元
    spatialIndex.addEntity(p1, p1->getBoundingBox());
    spatialIndex.addEntity(p2, p2->getBoundingBox());

    // 批量插入
    std::vector<std::pair<std::shared_ptr<MEngine::Entity>, MEngine::Ut::Rect2d>> batch = {
        {p3, p3->getBoundingBox()}
    };
    spatialIndex.addEntity(batch);

    std::cout << "Size: " << spatialIndex.size() << std::endl;

    // 查询相交
    MEngine::Ut::Rect2d queryBox(MEngine::Ut::Point(1.5, 1.5), MEngine::Ut::Point(2.5, 2.5));
    auto intersecting = spatialIndex.queryIntersects(queryBox);
    std::cout << "Intersecting entities:\n";
    for (const auto& entity : intersecting) {
        entity->print();
    }

    // 查询最近邻
    auto nearest = spatialIndex.queryNearest(MEngine::Ut::Point(1.5, 1.5), 2);
    std::cout << "Nearest 2 entities:\n";
    for (const auto& entity : nearest) {
        entity->print();
    }

    // 批量删除
    std::vector<std::pair<std::shared_ptr<MEngine::Entity>, MEngine::Ut::Rect2d>> toRemove = {
        {p2, p2->getBoundingBox()}
    };
    size_t removed = spatialIndex.removeEntity(toRemove);
    std::cout << "Removed " << removed << " entities, new size: " << spatialIndex.size() << std::endl;

    // 获取所有图元
    auto all = spatialIndex.getAllEntities();
    std::cout << "All entities:\n";
    for (const auto& entity : all) {
        entity->print();
    }

    return 0;
}

*/