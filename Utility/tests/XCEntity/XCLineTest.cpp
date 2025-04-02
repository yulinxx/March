#include <gtest/gtest.h>
#include "Ut/XCEntity/XCLine.h"

namespace UtlityTest {

class XCLineTest : public ::testing::Test {
protected:
    void SetUp() override {
        testLine = new XC::XCLine();
    }

    void TearDown() override {
        delete testLine;
    }

    XC::XCLine* testLine;
};

TEST_F(XCLineTest, ConstructorTest) {
    // 假设 XCLine 有一些默认属性，这里可以进行断言
    // 例如，假设 getLength 是获取长度的方法
    double expectedLength = 0.0; 
    EXPECT_DOUBLE_EQ(testLine->getLength(), expectedLength);
}

// 测试设置起点和终点的方法
TEST_F(XCLineTest, SetPointsTest) {
    // 假设 XCLine 有 setStartPoint 和 setEndPoint 方法
    XC::Point start(0, 0);
    XC::Point end(3, 4);
    testLine->setStartPoint(start);
    testLine->setEndPoint(end);
    double expectedLength = 5.0;
    EXPECT_DOUBLE_EQ(testLine->getLength(), expectedLength);
}

} // namespace UtlityTest