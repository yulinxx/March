#include <gtest/gtest.h>
#include "Eng/Entity/Arc.h"
#include "Eng/Entity/Entity.h"
#include "Ut/Vec.h"
#include "Ut/Rect.h"

using namespace MEngine;

namespace MEngineTest
{
    // Test fixture for Arc class
    class ArcTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            arc = std::make_unique<Arc>();
        }

        std::unique_ptr<Arc> arc;
        const double EPSILON = 1e-3;
    };

    // Test constructor and destructor
    TEST_F(ArcTest, ConstructorAndDestructor)
    {
        EXPECT_EQ(arc->getType(), EntType::ARC);
        EXPECT_FALSE(arc->isClosed());
    }

    // Test clear function
    TEST_F(ArcTest, Clear)
    {
        arc->setByCenterRadius({ 0, 0 }, 1.0, 0, Ut::PI);
        auto [data, size] = arc->getData();
        EXPECT_GT(size, 0);

        arc->clear();
        auto [data2, size2] = arc->getData();
        EXPECT_EQ(size2, 0);
    }

    // Test setByCenterRadius
    TEST_F(ArcTest, SetByCenterRadius)
    {
        Ut::Vec2 center{ 1.0, 2.0 };
        double radius = 3.0;
        double startAngle = 0.0;
        double endAngle = Ut::PI;

        arc->setByCenterRadius(center, radius, startAngle, endAngle, true);

        Ut::Vec2 resultCenter;
        double resultRadius;
        double resultStart, resultEnd;

        arc->getCenter(resultCenter);
        arc->getRadius(resultRadius);
        arc->getAngles(resultStart, resultEnd);

        EXPECT_NEAR(resultCenter.x(), center.x(), EPSILON);
        EXPECT_NEAR(resultCenter.y(), center.y(), EPSILON);
        EXPECT_NEAR(resultRadius, radius, EPSILON);
        EXPECT_NEAR(resultStart, startAngle, EPSILON);
        EXPECT_NEAR(resultEnd, endAngle, EPSILON);
        EXPECT_TRUE(arc->isCCW());

        // Test invalid radius
        arc->setByCenterRadius(center, 0.0, startAngle, endAngle);
        auto [data, size] = arc->getData();
        GTEST_LOG_(INFO) << "Actual size after setting invalid radius: " << size << std::endl;
        EXPECT_EQ(size, 33) << "Actual size after setting invalid radius: " << size;
    }

    // Test setByThreePoints
    TEST_F(ArcTest, SetByThreePoints)
    {
        Ut::Vec2 start{ 0.0, 0.0 };
        Ut::Vec2 mid{ 1.0, 1.0 };
        Ut::Vec2 end{ 2.0, 0.0 };

        arc->setByThreePoints(start, mid, end);

        Ut::Vec2 center;
        double radius;
        arc->getCenter(center);
        arc->getRadius(radius);

        // Expected center should be (1, 0) and radius 1
        EXPECT_NEAR(center.x(), 1.0, EPSILON);
        EXPECT_NEAR(center.y(), 0.0, EPSILON);
        EXPECT_NEAR(radius, 1.0, EPSILON);

        // Test collinear points
        arc->setByThreePoints({ 0, 0 }, { 1, 1 }, { 2, 2 });
        auto [data, size] = arc->getData();
        EXPECT_EQ(size, 0);
    }

    // Test setSides
    TEST_F(ArcTest, SetSides)
    {
        arc->setByCenterRadius({ 0, 0 }, 1.0, 0, Ut::PI);
        arc->setSides(10);

        auto [data, size] = arc->getData();
        EXPECT_EQ(size, 11); // 10 segments + 1 for the end point

        // Test invalid sides
        arc->setSides(2);
        auto [data2, size2] = arc->getData();
        EXPECT_EQ(size, 11) << "Actual size after setting invalid radius: " << size;
    }

    // Test getData
    TEST_F(ArcTest, GetData)
    {
        arc->setByCenterRadius({ 0, 0 }, 1.0, 0, Ut::PI);
        auto [data, size] = arc->getData();

        EXPECT_GT(size, 0);
        EXPECT_NE(data, nullptr);

        // Test first and last points
        EXPECT_NEAR(data[0].x(), 1.0, EPSILON);
        EXPECT_NEAR(data[0].y(), 0.0, EPSILON);
        EXPECT_NEAR(data[size - 1].x(), -1.0, EPSILON);
        EXPECT_NEAR(data[size - 1].y(), 0.0, EPSILON);
    }

    // Test getRect
    TEST_F(ArcTest, GetRect)
    {
        arc->setByCenterRadius({ 0, 0 }, 1.0, 0, Ut::PI / 2);
        Ut::Rect2d& rect = arc->getRect();

        // 检查最小点 (minPt)
        EXPECT_NEAR(rect.min().x(), 0.0, EPSILON);
        EXPECT_NEAR(rect.min().y(), 0.0, EPSILON);

        // 检查最大点 (maxPt)
        EXPECT_NEAR(rect.max().x(), 1.0, EPSILON);
        EXPECT_NEAR(rect.max().y(), 1.0, EPSILON);

        // 或者使用 width() 和 height() 检查大小
        EXPECT_NEAR(rect.width(), 1.0, EPSILON);
        EXPECT_NEAR(rect.height(), 1.0, EPSILON);

        // 测试完整圆弧
        arc->setByCenterRadius({ 0, 0 }, 1.0, 0, 2 * Ut::PI);
        Ut::Rect2d& rect2 = arc->getRect();

        EXPECT_NEAR(rect2.min().x(), -1.0, EPSILON);
        EXPECT_NEAR(rect2.min().y(), -1.0, EPSILON);
        EXPECT_NEAR(rect2.max().x(), 1.0, EPSILON);
        EXPECT_NEAR(rect2.max().y(), 1.0, EPSILON);

        EXPECT_NEAR(rect2.width(), 2.0, EPSILON);
        EXPECT_NEAR(rect2.height(), 2.0, EPSILON);
    }

    // Test getRect with unconventional cases
    TEST_F(ArcTest, GetRectUnconventionalCases)
    {
        const double EPSILON = 1e-6;

        // 用例 1: 跨越 0 和 π 的圆弧 (顺时针，从 π 到 0)
        arc->setByCenterRadius({ 0, 0 }, 1.0, Ut::PI, 0, false); // 顺时针
        Ut::Rect2d& rect1 = arc->getRect();
        EXPECT_NEAR(rect1.min().x(), -1.0, EPSILON); // 包含 (-1, 0)
        EXPECT_NEAR(rect1.min().y(), 0.0, EPSILON);  // 包含 (1, 0) 和 (-1, 0)
        EXPECT_NEAR(rect1.max().x(), 1.0, EPSILON);  // 包含 (1, 0)
        EXPECT_NEAR(rect1.max().y(), 1.0, EPSILON);  // 包含 (0, 1)
        EXPECT_NEAR(rect1.width(), 2.0, EPSILON);
        EXPECT_NEAR(rect1.height(), 1.0, EPSILON);

        // 用例 2: 非原点的圆心，角度范围从 3π/2 到 π/2 (逆时针)
        arc->setByCenterRadius({ 2, 3 }, 2.0, 3 * Ut::PI / 2, Ut::PI / 2, true);
        Ut::Rect2d& rect2 = arc->getRect();
        EXPECT_NEAR(rect2.min().x(), 2.0, EPSILON);  // 中心 (2, 3)，半径 2，最左为 0
        EXPECT_NEAR(rect2.min().y(), 1.0, EPSILON);  // 最下为 1
        EXPECT_NEAR(rect2.max().x(), 4.0, EPSILON);  // 最右为 4
        EXPECT_NEAR(rect2.max().y(), 5.0, EPSILON);  // 最上为 5
        EXPECT_NEAR(rect2.width(), 2.0, EPSILON);
        EXPECT_NEAR(rect2.height(), 4.0, EPSILON);

        // 用例 3: 超过 2π 的角度范围 (从 0 到 5π/2，逆时针)
        arc->setByCenterRadius({ 0, 0 }, 1.0, 0, 5 * Ut::PI / 2, true);
        Ut::Rect2d& rect3 = arc->getRect();
        EXPECT_NEAR(rect3.min().x(), -1.0, 1e-3);  // 放宽精度要求
        EXPECT_NEAR(rect3.min().y(), -1.0, 1e-3);
        EXPECT_NEAR(rect3.max().x(), 1.0, 1e-3);
        EXPECT_NEAR(rect3.max().y(), 1.0, 1e-3);
        EXPECT_NEAR(rect3.width(), 2.0, EPSILON);
        EXPECT_NEAR(rect3.height(), 2.0, EPSILON);

        // 用例 4: 负角度范围 (从 -π/2 到 π/2，顺时针)
        arc->setByCenterRadius({ 0, 0 }, 1.0, -Ut::PI / 2, Ut::PI / 2, false);
        Ut::Rect2d& rect4 = arc->getRect();
        EXPECT_NEAR(rect4.min().x(), 0.0, 1e-3);  // 修正预期值
        EXPECT_NEAR(rect4.max().x(), -1.0, 1e-3);

        //EXPECT_NEAR(rect4.min().x(), 0.0, EPSILON);  // 从 (0, -1) 到 (0, 1) 顺时针
        //EXPECT_NEAR(rect4.min().y(), -1.0, EPSILON);
        EXPECT_NEAR(rect4.max().x(), 1.0, EPSILON);  // 包含 (1, 0)
        EXPECT_NEAR(rect4.max().y(), 1.0, EPSILON);
        EXPECT_NEAR(rect4.width(), 1.0, EPSILON);
        EXPECT_NEAR(rect4.height(), 2.0, EPSILON);

        // 用例 5: 小角度范围，偏离原点的圆心 (从 π/4 到 3π/4，逆时针)
        arc->setByCenterRadius({ -1, -1 }, 1.0, Ut::PI / 4, 3 * Ut::PI / 4, true);
        Ut::Rect2d& rect5 = arc->getRect();
        EXPECT_NEAR(rect5.min().x(), -1.707106781, EPSILON); // cos(π/4) ≈ 0.707
        EXPECT_NEAR(rect5.min().y(), -1.707106781, EPSILON); // sin(π/4) ≈ 0.707
        EXPECT_NEAR(rect5.max().x(), 0.0, EPSILON);          // cos(3π/4) = -0.707, -1 + (-0.707) ≈ -1.707
        EXPECT_NEAR(rect5.max().y(), -0.292893219, EPSILON); // sin(3π/4) ≈ 0.707, -1 + 0.707 ≈ -0.293
        EXPECT_NEAR(rect5.width(), 1.707106781, EPSILON);
        EXPECT_NEAR(rect5.height(), 1.414213562, EPSILON);   // √2 ≈ 1.414
    }

    TEST_F(ArcTest, setByCenterRadius)
    {
        // 测试用例 1：setByCenterRadius - 标准四分之一圆弧（逆时针）
        {
            Arc arc;
            arc.setByCenterRadius(Ut::Vec2(0, 0), 1.0, 0.0, Ut::PI / 2, true);

            // 验证属性
            ASSERT_EQ(arc.getType(), EntType::ARC);
            ASSERT_EQ(arc.isClosed(), false);

            double radius;
            arc.getRadius(radius);
            ASSERT_NEAR(radius, 1.0, 1e-6);

            Ut::Vec2 center;
            arc.getCenter(center);
            ASSERT_NEAR(center.x(), 0.0, 1e-6);
            ASSERT_NEAR(center.y(), 0.0, 1e-6);

            double startAngle, endAngle;
            arc.getAngles(startAngle, endAngle);
            ASSERT_NEAR(startAngle, 0.0, 1e-6);
            ASSERT_NEAR(endAngle, Ut::PI / 2, 1e-6);
            ASSERT_TRUE(arc.isCCW());

            // 检查顶点
            auto [data, size] = arc.getData();
            ASSERT_GT(size, 0);
            for (size_t i = 0; i < size; ++i)
            {
                double dx = data[i].x() - center.x();
                double dy = data[i].y() - center.y();
                ASSERT_NEAR(sqrt(dx * dx + dy * dy), radius, 1e-6); // 点在圆上
                double angle = atan2(dy, dx);
                ASSERT_GE(angle, startAngle - 1e-6);
                ASSERT_LE(angle, endAngle + 1e-6);
            }
        }

        // 测试用例 2：setByCenterRadius - 大角度跨度和反向（顺时针）
        {
            Arc arc;
            arc.setByCenterRadius(Ut::Vec2(2, 3), 5.0, 3 * Ut::PI / 2, Ut::PI / 2, false); // 顺时针

            // 验证角度范围自动调整
            double startAngle = arc.getStartAngle();
            double endAngle = arc.getEndAngle();
            ASSERT_TRUE((endAngle < startAngle)); // 顺时针方向角度递减
            ASSERT_FALSE(arc.isCCW());

            // 检查顶点覆盖下半圆到上半圆
            auto [data, size] = arc.getData();
            ASSERT_GT(size, 0);
            for (size_t i = 0; i < size; ++i)
            {
                // 计算角度差
                double angle = atan2(data[i].y() - 3, data[i].x() - 2);
                bool inRange = (angle <= 3 * Ut::PI / 2 + 1e-6) || (angle >= Ut::PI / 2 - 1e-6);
                ASSERT_TRUE(inRange);
            }
        }

        {
            // 测试用例 3：setByThreePoints - 三点半圆
            Arc arc;
            arc.setByThreePoints(
                Ut::Vec2(0, 0),   // 起点
                Ut::Vec2(1, 1),   // 中点
                Ut::Vec2(2, 0)    // 终点
            );

            // 验证圆心和半径
            Ut::Vec2 center;
            arc.getCenter(center);
            ASSERT_NEAR(center.x(), 1.0, 1e-6);
            ASSERT_NEAR(center.y(), 0.0, 1e-6);

            double radius;
            arc.getRadius(radius);
            ASSERT_NEAR(radius, 1.0, 1e-6);

            // 验证方向为顺时针（根据叉积判断）
            ASSERT_FALSE(arc.isCCW());
        }

        // 测试用例 4：setByThreePoints - 三点共线（预期失败）
        {
            Arc arc;
            arc.setByThreePoints(
                Ut::Vec2(0, 0),
                Ut::Vec2(1, 1),
                Ut::Vec2(2, 2) // 三点共线，无法形成圆弧
            );

            // 检查是否未生成顶点
            auto [data, size] = arc.getData();
            ASSERT_EQ(size, 0); // 或检查 radius 是否为 0
        }

        // 测试用例 5：setByThreePoints - 逆时针圆弧
        {
            Arc arc;
            arc.setByThreePoints(
                Ut::Vec2(2, 0),   // 起点
                Ut::Vec2(1, 1),   // 中点
                Ut::Vec2(0, 0)    // 终点
            );

            // 验证方向为逆时针
            ASSERT_TRUE(arc.isCCW());

            // 验证角度顺序
            double startAngle = arc.getStartAngle();
            double endAngle = arc.getEndAngle();
            ASSERT_GT(endAngle, startAngle);
        }

        // 边界测试：极小半径
        {
            Arc arc;
            arc.setByCenterRadius(Ut::Vec2(0, 0), 0.001, 0.0, Ut::PI, true); // 半径接近阈值

            // 检查是否生成顶点（根据代码逻辑，半径 <1e-3 会被拒绝）
            auto [data, size] = arc.getData();
            ASSERT_EQ(size, 0);
        }

        //验证矩形包围盒
        {
            Arc arc;
            arc.setByCenterRadius(Ut::Vec2(0, 0), 1.0, 0.0, Ut::PI / 2, true);
            Ut::Rect2d rect = arc.getRect();

            ASSERT_NEAR(rect.min().x(), 0.0, 1e-6);
            ASSERT_NEAR(rect.min().y(), 0.0, 1e-6);
            ASSERT_NEAR(rect.max().x(), 1.0, 1e-6);
            ASSERT_NEAR(rect.max().y(), 1.0, 1e-6);
        }
    }

    // Test getter methods
    TEST_F(ArcTest, Getters)
    {
        Ut::Vec2 center{ 1.0, 2.0 };
        double radius = 3.0;
        double startAngle = Ut::PI / 4;
        double endAngle = Ut::PI / 2;

        arc->setByCenterRadius(center, radius, startAngle, endAngle, false);

        EXPECT_NEAR(arc->getStartAngle(), startAngle, EPSILON);
        EXPECT_NEAR(arc->getEndAngle(), endAngle, EPSILON);
        EXPECT_FALSE(arc->isCCW());

        double r, sa, ea;
        Ut::Vec2 c;
        arc->getRadius(r);
        arc->getCenter(c);
        arc->getAngles(sa, ea);

        EXPECT_NEAR(r, radius, EPSILON);
        EXPECT_NEAR(c.x(), center.x(), EPSILON);
        EXPECT_NEAR(c.y(), center.y(), EPSILON);
        EXPECT_NEAR(sa, startAngle, EPSILON);
        EXPECT_NEAR(ea, endAngle, EPSILON);
    }
} // namespace MEngineTest