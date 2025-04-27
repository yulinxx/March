#ifndef ENTITYINDEX_H
#define ENTITYINDEX_H

#include "IndexDef.h"
#include "Scene/SceneComponent.h"

using namespace Ut;
namespace MEngine
{
    using RTreeRectEnt = std::pair<Ut::Rect2d, std::shared_ptr<Entity>>;
    using EntRTree = bgi::rtree<RTreeRectEnt, bgi::quadratic<16>>;

    class MENGINE_API EntityIndex : public SceneComponent
    {
    public:
        EntityIndex();

    public:
        virtual void addEntity(std::shared_ptr<Entity> entity) override;
        virtual void removeEntity(std::shared_ptr<Entity> entity) override;

    public:
        // 获取所有图元
        std::vector<std::shared_ptr<Entity>> getAllEntities() const;

        // 框选（完全包含在矩形内的实体）
        std::vector<std::shared_ptr<Entity>> getEntities(const Ut::Rect2d& rect) const;

        // 交选（与矩形相交的实体）
        std::vector<std::shared_ptr<Entity>> getCrossEntities(const Ut::Rect2d& rect) const;

        // 反选（不在矩形内的实体）
        std::vector<std::shared_ptr<Entity>> getInverseSelectedEntities(const Ut::Rect2d& rect) const;

        std::vector<std::shared_ptr<Entity>> getNearestEntities(const Ut::Vec2d& point, size_t k = 1) const;

        // 获取所有图元的最大包围矩形
        Ut::Rect2d getBoundingBox() const;

        void clear();

        size_t size() const;

        bool empty() const;

    private:
        EntRTree m_entTree;
    };
} // namespace MEngine

#endif // ENTITYINDEX_H
