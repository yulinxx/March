#include "gtest/gtest.h"
#include "Entity/Point.h"
#include "Entity/Line.h"
#include "Entity/Arc.h"
#include "Entity/Circle.h"
#include "Entity/Polyline.h"
#include "Entity/PolyBspline.h"
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
        EXPECT_DOUBLE_EQ(testLine->m_basePt.x(), 0.0);
        EXPECT_DOUBLE_EQ(testLine->m_basePt.y(), 0.0);
        EXPECT_DOUBLE_EQ(testLine->m_secPoint.x(), 3.0);
        EXPECT_DOUBLE_EQ(testLine->m_secPoint.y(), 4.0);
    }

    TEST_F(LineTest, LineLength)
    {
        // 3-4-5直角三角形的斜边长度应为5
        auto ptS = testLine->m_basePt;
        auto ptE = testLine->m_secPoint;
        double len = std::sqrt(std::pow(ptE.x() - ptS.x(), 2) + std::pow(ptE.y() - ptS.y(), 2));
        // EXPECT_DOUBLE_EQ(len, 5.0);
        EXPECT_NEAR(len, 5.0, 1e-6);
    }

    // TEST_F(LineTest, LineDirection) {
    //     auto direction = testLine->directionVector();
    //     EXPECT_DOUBLE_EQ(direction.x(), 3.0);
    //     EXPECT_DOUBLE_EQ(direction.y(), 4.0);
    // }
} // namespace MEngineTest