#include <gtest/gtest.h>
#include "Ut/XCEntity/XCCircle.h"

namespace UtlityTest {

class XCCircleTest : public ::testing::Test {
protected:
    void SetUp() override {
        testCircle = new XC::XCCircle();
    }

    void TearDown() override {
        delete testCircle;
    }

    XC::XCCircle* testCircle;
};

TEST_F(XCCircleTest, ConstructorTest) {
    // 假设 XCCircle 有一些默认属性，这里可以进行断言
    // 例如，假设 getRadius 是获取半径的方法
    double expectedRadius = 0.0; 
    // EXPECT_DOUBLE_EQ(testCircle->getRadius(), expectedRadius);
}

// 测试设置半径的方法
TEST_F(XCCircleTest, SetRadiusTest) {
    double newRadius = 5.0;
    // testCircle->setRadius(newRadius);
    // EXPECT_DOUBLE_EQ(testCircle->getRadius(), newRadius);
}

// 测试计算面积的方法
TEST_F(XCCircleTest, CalculateAreaTest) {
    double radius = 5.0;
    // testCircle->setRadius(radius);
    // double expectedArea = M_PI * radius * radius;
    // double actualArea = testCircle->calculateArea();
    // EXPECT_DOUBLE_EQ(actualArea, expectedArea);
}

} // namespace UtlityTest