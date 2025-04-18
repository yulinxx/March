#include "gtest/gtest.h"
#include "Entity/Point.h"
#include "Entity/Line.h"
#include "Entity/Arc.h"
#include "Entity/Circle.h"
#include "Entity/Polyline.h"
#include "Entity/CubicBSpline.h"
#include "Entity/Text.h"
#include "Ut/Vec.h"

namespace MEngineTest
{
    class LineTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // 创建测试用的直线（从原点(0,0)到(3,4)）
            auto a = Ut::Vec2d(0, 0);
            auto b = Ut::Vec2d(3, 4);
            testLine = new MEngine::Line(a, b);
        }

        void TearDown() override
        {
            //delete testLine;
        }

        MEngine::Line* testLine;
    };

    TEST_F(LineTest, LineConstructor)
    {
        Ut::Vec2d ptS, ptE;
        testLine->getPoints(ptS, ptE);
        EXPECT_DOUBLE_EQ(ptS.x(), 0.0);
        EXPECT_DOUBLE_EQ(ptS.y(), 0.0);
        EXPECT_DOUBLE_EQ(ptE.x(), 3.0);
        EXPECT_DOUBLE_EQ(ptE.y(), 4.0);

        auto& rect = testLine->getRect();
        EXPECT_DOUBLE_EQ(rect.width(), 3.0);
        EXPECT_DOUBLE_EQ(rect.height(), 4.0);
    }

    TEST_F(LineTest, LineLength)
    {
        // 3-4-5直角三角形的斜边长度应为5
        Ut::Vec2d  ptS, ptE;
        testLine->getPoints(ptS, ptE);
        double len = std::sqrt(std::pow(ptE.x() - ptS.x(), 2) + std::pow(ptE.y() - ptS.y(), 2));
        double len2 = testLine->getLength();

        EXPECT_NEAR(len, 5.0, 1e-3);
        EXPECT_NEAR(len2, 5.0, 1e-3);

        testLine->setPoints(Ut::Vec2d(7, 8), Ut::Vec2d(10, 15));
        auto& rect = testLine->getRect();
        EXPECT_DOUBLE_EQ(rect.width(), 3.0);
        EXPECT_DOUBLE_EQ(rect.height(), 7.0);

        double dLen = testLine->getLength();
        EXPECT_NEAR(dLen, 7.6157, 1e-3);
    }

    // TEST_F(LineTest, LineDirection) {
    //     auto direction = testLine->directionVector();
    //     EXPECT_DOUBLE_EQ(direction.x(), 3.0);
    //     EXPECT_DOUBLE_EQ(direction.y(), 4.0);
    // }
} // namespace MEngineTest