#ifndef ENTITYINDEX_H
#define ENTITYINDEX_H

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "Entity/Entity.h"
#include "MEngineAPI.h"
#include "Ut/Rect.h"
#include <memory>
#include <vector>

namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            template <typename T, size_t N>
            struct tag<Ut::Vec<T, N>>
            {
                using type = point_tag;
            };

            template <typename T, size_t N>
            struct coordinate_type<Ut::Vec<T, N>>
            {
                using type = T;
            };

            template <typename T, size_t N>
            struct coordinate_system<Ut::Vec<T, N>>
            {
                using type = cs::cartesian;
            };

            template <typename T, size_t N>
            struct dimension<Ut::Vec<T, N>> : boost::mpl::int_<static_cast<int>(N)>
            {
            };

            template <typename T, size_t N>
            struct access<Ut::Vec<T, N>, 0>
            {
                static T get(const Ut::Vec<T, N>& p)
                {
                    return p[0];
                }
                static void set(Ut::Vec<T, N>& p, T value)
                {
                    p[0] = value;
                }
            };

            template <typename T, size_t N>
            struct access<Ut::Vec<T, N>, 1>
            {
                static T get(const Ut::Vec<T, N>& p)
                {
                    static_assert(N >= 2, "Dimension must be >= 2"); return p[1];
                }
                static void set(Ut::Vec<T, N>& p, T value)
                {
                    static_assert(N >= 2, "Dimension must be >= 2"); p[1] = value;
                }
            };

            template <typename T, size_t N>
            struct access<Ut::Vec<T, N>, 2>
            {
                static T get(const Ut::Vec<T, N>& p)
                {
                    static_assert(N >= 3, "Dimension must be >= 3"); return p[2];
                }
                static void set(Ut::Vec<T, N>& p, T value)
                {
                    static_assert(N >= 3, "Dimension must be >= 3"); p[2] = value;
                }
            };

            // 为 Ut::Rect<T, DIM> 定义 Boost Geometry Traits
            template <typename T, int DIM>
            struct tag<Ut::Rect<T, DIM>>
            {
                using type = box_tag;
            };

            template <typename T, int DIM>
            struct point_type<Ut::Rect<T, DIM>>
            {
                using type = Ut::Vec<T, DIM>;
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, min_corner, 0>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    return b.min()[0];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    b.setMin(Ut::Vec<T, DIM>(value, b.min()[1]));
                }
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, min_corner, 1>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); return b.min()[1];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); b.setMin(Ut::Vec<T, DIM>(b.min()[0], value));
                }
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, max_corner, 0>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    return b.max()[0];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    b.setMax(Ut::Vec<T, DIM>(value, b.max()[1]));
                }
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, max_corner, 1>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); return b.max()[1];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); b.setMax(Ut::Vec<T, DIM>(b.max()[0], value));
                }
            };
        }
    }
} // namespace boost::geometry::traits

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using namespace Ut;
namespace MEngine
{
    using RTreeValue = std::pair<Ut::Rect2d, std::shared_ptr<Entity>>;
    using RTree = bgi::rtree<RTreeValue, bgi::quadratic<16>>;

    // 空间索引管理类声明
    class MENGINE_API EntityIndex
    {
    public:
        EntityIndex();

        // 插入单个实体及其边界框
        void insert(std::shared_ptr<Entity> entity, const Ut::Rect2d& box);
        void insert(Entity* entity, const Ut::Rect2d& box); // 兼容原始指针

        // 批量插入
        void insertBatch(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities);

        // 删除单个实体及其边界框
        bool remove(const std::shared_ptr<Entity>& entity, const Ut::Rect2d& box);
        bool remove(Entity* entity, const Ut::Rect2d& box);

        // 批量删除
        size_t removeBatch(const std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>>& entities);

        // 查询与给定矩形相交的实体
        std::vector<std::shared_ptr<Entity>> queryIntersects(const Ut::Rect2d& queryBox) const;

        // 查询包含给定点的实体
        std::vector<std::shared_ptr<Entity>> queryContains(const Ut::Point& point) const;

        // 查询距离点最近的k个实体
        std::vector<std::shared_ptr<Entity>> queryNearest(const Ut::Point& point, size_t k) const;

        // 获取所有实体
        std::vector<std::shared_ptr<Entity>> getAllEntities() const;

        void clear();

        size_t size() const;

        bool empty() const;

    private:
        RTree m_entTree; // R-tree实例
    };
} // namespace MEngine

#endif // ENTITYINDEX_H

/*

#include "EntityIndex.h"
#include "PointEntity.h"
#include <iostream>

int main() {
    MEngine::EntityIndex spatialIndex;

    // 创建实体
    auto p1 = std::make_shared<MEngine::PointEntity>(1.0, 1.0);
    auto p2 = std::make_shared<MEngine::PointEntity>(2.0, 2.0);
    auto p3 = std::make_shared<MEngine::PointEntity>(3.0, 3.0);

    // 插入单个实体
    spatialIndex.insert(p1, p1->getBoundingBox());
    spatialIndex.insert(p2, p2->getBoundingBox());

    // 批量插入
    std::vector<std::pair<std::shared_ptr<MEngine::Entity>, MEngine::Ut::Rect2d>> batch = {
        {p3, p3->getBoundingBox()}
    };
    spatialIndex.insertBatch(batch);

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
    size_t removed = spatialIndex.removeBatch(toRemove);
    std::cout << "Removed " << removed << " entities, new size: " << spatialIndex.size() << std::endl;

    // 获取所有实体
    auto all = spatialIndex.getAllEntities();
    std::cout << "All entities:\n";
    for (const auto& entity : all) {
        entity->print();
    }

    return 0;
}

*/