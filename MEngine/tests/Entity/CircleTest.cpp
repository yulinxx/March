#include "gtest/gtest.h"
#include "Eng/Entity/Circle.h"
#include "Ut/Vec.h"

namespace MEngineTest
{

    class CircleTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            circle = new MEngine::Circle();
        }

        void TearDown() override
        {
            delete circle;
        }

        MEngine::Circle* circle;
    };

    // 测试构造函数和析构函数
    TEST_F(CircleTest, ConstructorAndDestructor)
    {
        EXPECT_NE(circle, nullptr);
    }

    // 测试 clear 函数
    TEST_F(CircleTest, ClearFunction)
    {
        circle->clear();
        auto data = circle->getData();
        EXPECT_EQ(data.second, 0); // 顶点数量应该为 0
    }

    // 测试 getData 函数
    TEST_F(CircleTest, GetDataFunction)
    {
        circle->setByCenterRadius(Ut::Vec2(0, 0), 1.0);
        auto data = circle->getData();
        EXPECT_NE(data.first, nullptr);
        EXPECT_GT(data.second, 0); // 顶点数量应该大于 0
    }

    // 测试 getRect 函数
    TEST_F(CircleTest, GetRectFunction)
    {
        Ut::Rect2d& rect = circle->getRect();
        // 这里可以添加更多验证逻辑，取决于 getRect 函数的实现
        EXPECT_EQ(rect, Ut::Rect2d()); // 默认情况下，矩形应该是空的
    }

    // 测试 setByCenterPt 函数
    TEST_F(CircleTest, SetByCenterPtFunction)
    {
        Ut::Vec2 center(0, 0);
        Ut::Vec2 end(1, 0);
        circle->setByCenterPt(center, end);
        double radius;
        circle->getRadius(radius);
        EXPECT_DOUBLE_EQ(radius, 1.0);
    }

    // 测试 setByCenterRadius 函数
    TEST_F(CircleTest, SetByCenterRadiusFunction)
    {
        Ut::Vec2 center(0, 0);
        double radius = 2.0;
        circle->setByCenterRadius(center, radius);
        double retrievedRadius;
        circle->getRadius(retrievedRadius);
        EXPECT_DOUBLE_EQ(retrievedRadius, radius);
    }

    // 测试 setByDiameter 函数
    TEST_F(CircleTest, SetByDiameterFunction)
    {
        Ut::Vec2 start(-1, 0);
        Ut::Vec2 end(1, 0);
        circle->setByDiameter(start, end);
        double radius;
        circle->getRadius(radius);
        EXPECT_DOUBLE_EQ(radius, 2.0);
    }

    // 测试 setByThreePoints 函数
    TEST_F(CircleTest, SetByThreePointsFunction)
    {
        Ut::Vec2 p1(1, 0);
        Ut::Vec2 p2(0, 1);
        Ut::Vec2 p3(-1, 0);
        circle->setByThreePoints(p1, p2, p3);
        double radius;
        circle->getRadius(radius);
        EXPECT_DOUBLE_EQ(radius, 1.0);
    }

    // 测试 setSides 函数
    TEST_F(CircleTest, SetSidesFunction)
    {
        size_t nSides = 10;
        circle->setByCenterRadius({ 10, 10 }, 5);
        circle->setSides(nSides);
        auto data = circle->getData();
        EXPECT_EQ(data.second, nSides + 1); // 顶点数量应该等于边数 + 1
    }

    // 测试 getRadius 函数
    TEST_F(CircleTest, GetRadiusFunction)
    {
        Ut::Vec2 center(0, 0);
        double radius = 3.0;
        circle->setByCenterRadius(center, radius);
        double retrievedRadius;
        circle->getRadius(retrievedRadius);
        EXPECT_DOUBLE_EQ(retrievedRadius, radius);
    }

    // 测试 getCenter 函数
    TEST_F(CircleTest, GetCenterFunction)
    {
        Ut::Vec2 center(1, 2);
        double radius = 1.0;
        circle->setByCenterRadius(center, radius);
        Ut::Vec2 retrievedCenter;
        circle->getCenter(retrievedCenter);
        EXPECT_DOUBLE_EQ(retrievedCenter.x(), center.x());
        EXPECT_DOUBLE_EQ(retrievedCenter.y(), center.y());
    }

    // 测试 getLength 函数
    TEST_F(CircleTest, GetLengthFunction)
    {
        Ut::Vec2 center(0, 0);
        double radius = 1.0;
        circle->setByCenterRadius(center, radius);
        double length = circle->getLength();
        EXPECT_DOUBLE_EQ(length, 2 * Ut::PI * radius);
    }

    // 测试 isCCW 函数
    TEST_F(CircleTest, IsCCWFunction)
    {
        Ut::Vec2 center(0, 0);
        Ut::Vec2 end(1, 0);
        circle->setByCenterPt(center, end, true);
        EXPECT_TRUE(circle->isCCW());
        circle->setByCenterPt(center, end, false);
        EXPECT_FALSE(circle->isCCW());
    }

} // namespace MEngineTest



//#include "gtest/gtest.h"
//#include "Eng/Entity/Circle.h"
//#include "Ut/Vec.h"
//
//namespace MEngineTest
//{
//
//    class CircleTest : public ::testing::Test
//    {
//    protected:
//        void SetUp() override
//        {
//            circle = new MEngine::Circle();
//        }
//
//        void TearDown() override
//        {
//            delete circle;
//        }
//
//        MEngine::Circle* circle;
//    };
//
//    // 测试构造函数和析构函数
//    TEST_F(CircleTest, ConstructorAndDestructor)
//    {
//        EXPECT_NE(circle, nullptr);
//    }
//
//    // 测试 clear 函数
//    TEST_F(CircleTest, ClearFunction)
//    {
//        circle->clear();
//    }
//
//    // 测试 getData 函数
//    TEST_F(CircleTest, GetDataFunction)
//    {
//        auto data = circle->getData();
//        EXPECT_NE(data.first, nullptr);
//        EXPECT_GE(data.second, 0);
//    }
//
//    // 测试 getRect 函数
//    TEST_F(CircleTest, GetRectFunction)
//    {
//        Ut::Rect2d& rect = circle->getRect();
//        // 这里可以添加更多验证逻辑，取决于 getRect 函数的实现
//    }
//
//    // 测试 setByCenterPt 函数
//    TEST_F(CircleTest, SetByCenterPtFunction)
//    {
//        Ut::Vec2 center(0, 0);
//        Ut::Vec2 end(1, 0);
//        circle->setByCenterPt(center, end);
//        double radius;
//        circle->getRadius(radius);
//        EXPECT_DOUBLE_EQ(radius, 1);
//    }
//
//    // 测试 setByCenterRadius 函数
//    TEST_F(CircleTest, SetByCenterRadiusFunction)
//    {
//        Ut::Vec2 center(0, 0);
//        double radius = 2;
//        circle->setByCenterRadius(center, radius);
//        double retrievedRadius;
//        circle->getRadius(retrievedRadius);
//        EXPECT_DOUBLE_EQ(retrievedRadius, radius);
//    }
//
//    // 测试 setByDiameter 函数
//    TEST_F(CircleTest, SetByDiameterFunction)
//    {
//        Ut::Vec2 start(-1, 0);
//        Ut::Vec2 end(1, 0);
//        circle->setByDiameter(start, end);
//        double radius;
//        circle->getRadius(radius);
//        EXPECT_DOUBLE_EQ(radius, 1);
//    }
//
//    // 测试 setByThreePoints 函数
//    TEST_F(CircleTest, SetByThreePointsFunction)
//    {
//        Ut::Vec2 p1(1, 0);
//        Ut::Vec2 p2(0, 1);
//        Ut::Vec2 p3(-1, 0);
//        circle->setByThreePoints(p1, p2, p3);
//        double radius;
//        circle->getRadius(radius);
//        EXPECT_DOUBLE_EQ(radius, 1);
//    }
//
//    // 测试 setSides 函数
//    TEST_F(CircleTest, SetSidesFunction)
//    {
//        size_t nSides = 10;
//        circle->setSides(nSides);
//        // 这里可以添加更多验证逻辑，取决于 setSides 函数的实现
//    }
//
//    // 测试 getRadius 函数
//    TEST_F(CircleTest, GetRadiusFunction)
//    {
//        Ut::Vec2 center(0, 0);
//        double radius = 3;
//        circle->setByCenterRadius(center, radius);
//        double retrievedRadius;
//        circle->getRadius(retrievedRadius);
//        EXPECT_DOUBLE_EQ(retrievedRadius, radius);
//    }
//
//    // 测试 getCenter 函数
//    TEST_F(CircleTest, GetCenterFunction)
//    {
//        Ut::Vec2 center(1, 2);
//        double radius = 1;
//        circle->setByCenterRadius(center, radius);
//        Ut::Vec2 retrievedCenter;
//        circle->getCenter(retrievedCenter);
//        EXPECT_DOUBLE_EQ(retrievedCenter.x(), center.x());
//        EXPECT_DOUBLE_EQ(retrievedCenter.y(), center.y());
//    }
//
//    // 测试 getLength 函数
//    TEST_F(CircleTest, GetLengthFunction)
//    {
//        Ut::Vec2 center(0, 0);
//        double radius = 1;
//        circle->setByCenterRadius(center, radius);
//        double length = circle->getLength();
//        EXPECT_DOUBLE_EQ(length, 2 * Ut::PI * radius);
//    }
//
//    // 测试 isCCW 函数
//    TEST_F(CircleTest, IsCCWFunction)
//    {
//        Ut::Vec2 center(0, 0);
//        Ut::Vec2 end(1, 0);
//        circle->setByCenterPt(center, end, true);
//        EXPECT_TRUE(circle->isCCW());
//        circle->setByCenterPt(center, end, false);
//        EXPECT_FALSE(circle->isCCW());
//    }
//
//} // namespace MEngineTest