#include "gtest/gtest.h"
#include "Scene/EntityIndex.h"
#include "Scene/PointEntity.h" // 假设有PointEntity测试类

namespace MEngine::Test
{
    class EntityIndexTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // 创建测试用实体
            p1 = std::make_shared<PointEntity>(1.0, 1.0);
            p2 = std::make_shared<PointEntity>(2.0, 2.0);
            p3 = std::make_shared<PointEntity>(3.0, 3.0);
        }

        std::shared_ptr<Entity> p1, p2, p3;
        EntityIndex index;
    };

    TEST_F(EntityIndexTest, InsertSingleEntity)
    {
        index.insert(p1, Ut::Rect2d(0, 0, 2, 2));
        EXPECT_EQ(index.size(), 1);
    }

    TEST_F(EntityIndexTest, BatchInsertAndQuery)
    {
        std::vector<std::pair<std::shared_ptr<Entity>, Ut::Rect2d>> entities = {
            {p1, p1->getBoundingBox()},
            {p2, p2->getBoundingBox()}
        };

        index.insertBatch(entities);
        auto results = index.getAllEntities();
        ASSERT_EQ(results.size(), 2);
    }

    TEST_F(EntityIndexTest, RemoveEntity)
    {
        index.insert(p1, Ut::Rect2d(0, 0, 2, 2));
        bool removed = index.remove(p1, Ut::Rect2d(0, 0, 2, 2));
        EXPECT_TRUE(removed);
        EXPECT_EQ(index.size(), 0);
    }

    TEST_F(EntityIndexTest, SpatialQuery)
    {
        index.insert(p1, Ut::Rect2d(0, 0, 1, 1));
        index.insert(p2, Ut::Rect2d(2, 2, 3, 3));

        auto intersects = index.queryIntersects(Ut::Rect2d(0.5, 0.5, 1.5, 1.5));
        EXPECT_EQ(intersects.size(), 1);
    }

    TEST_F(EntityIndexTest, NearestNeighbor)
    {
        index.insert(p1, Ut::Rect2d(1, 1, 1, 1));
        index.insert(p2, Ut::Rect2d(5, 5, 1, 1));

        auto nearest = index.queryNearest(Ut::Point(3, 3), 1);
        ASSERT_FALSE(nearest.empty());
        EXPECT_EQ(nearest[0], p2);
    }
} // namespace MEngine::Test