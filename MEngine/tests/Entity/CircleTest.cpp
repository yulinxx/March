#include "gtest/gtest.h"
#include "Entity/Circle.h"

namespace MEngineTest
{
    class CircleTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // testCircle = new MEngine::Circle(Ut::Vec2d(1,1), 3.0);
        }

        void TearDown() override
        {
            // delete testCircle;
        }

        MEngine::Circle* testCircle;
    };

    TEST_F(CircleTest, CircleRadius)
    {
        // EXPECT_DOUBLE_EQ(testCircle->radius(), 3.0);
    }

    TEST_F(CircleTest, CircleCircumference)
    {
        // EXPECT_NEAR(testCircle->circumference(), 2 * M_PI * 3.0, 1e-6);
    }
} // namespace MEngineTest