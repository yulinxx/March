#include "gtest/gtest.h"
#include "Entity/Line.h"
#include "Scene/OrderManager.h"

using namespace MEngine;

class OrderManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        for (int i = 0; i < 100; i++)
        {
            Line* line = new Line();
            line->setId(i);
            //line->m_basePt.x() = i;
            auto& basePt = line->getBasePoint();
            basePt.x() = i;
            line->setBasePoint(basePt);
            m_vLines.push_back(line);
        }
    }

    void TearDown() override
    {
        for (auto line : m_vLines)
        {
            delete line;
        }
    }

    OrderManager manager;
    std::vector<Line*> m_vLines;
};

// - 添加了图元顺序一致性验证
// - 包含边界条件测试（首尾元素操作）
// - 验证移动操作后的位置修正逻辑
// - 通过类型转换验证具体派生类属性
// - 覆盖了不同位置的操作场景（开头/中间/结尾）
TEST_F(OrderManagerTest, EntityOrderConsistency)
{
    // 添加全部测试对象
    for (auto line : m_vLines)
    {
        manager.addEntity(line);
    }

    auto& entities = manager.getOrderedEntities();
    ASSERT_EQ(entities.size(), 100);

    // 验证初始添加顺序
    for (size_t i = 0; i < entities.size(); ++i)
    {
        EXPECT_EQ(static_cast<Line*>(entities[i])->getId(), i);
    }
}

TEST_F(OrderManagerTest, RemoveMiddleEntity)
{
    manager.addEntity(m_vLines[50]);
    ASSERT_TRUE(manager.removeEntity(m_vLines[50]));
    EXPECT_TRUE(manager.getOrderedEntities().empty());
}

TEST_F(OrderManagerTest, SwapEdgeCases)
{
    manager.addEntity(m_vLines[0]);
    manager.addEntity(m_vLines[99]);

    manager.swapEntities(m_vLines[0], m_vLines[99]);
    auto& entities = manager.getOrderedEntities();
    EXPECT_EQ(entities[0], m_vLines[99]);
    EXPECT_EQ(entities[1], m_vLines[0]);
}

TEST_F(OrderManagerTest, MoveEntityToExtremePositions)
{
    // 添加前三个对象
    manager.addEntity(m_vLines[0]);
    manager.addEntity(m_vLines[1]);
    manager.addEntity(m_vLines[2]);

    // 测试移动到开头
    manager.moveEntityToPos(m_vLines[2], 0);
    auto& entities = manager.getOrderedEntities();
    EXPECT_EQ(entities[0], m_vLines[2]);

    // 测试越界位置自动修正
    manager.moveEntityToPos(m_vLines[1], 100);
    EXPECT_EQ(entities.back(), m_vLines[1]);
}