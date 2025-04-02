#include "gtest/gtest.h"
#include "Entity/Point.h"

namespace MEngineTest
{
    class PointTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // testPoint = new MEngine::Point(Ut::Vec2d(2.5, 3.5));
            testPoint = new MEngine::Point();
        }

        void TearDown() override
        {
            delete testPoint;
        }

        MEngine::Point* testPoint;
    };

    TEST_F(PointTest, PointCoordinates)
    {
        // EXPECT_DOUBLE_EQ(testPoint->x(), 2.5);
        // EXPECT_DOUBLE_EQ(testPoint->y(), 3.5);
    }
} // namespace MEngineTest