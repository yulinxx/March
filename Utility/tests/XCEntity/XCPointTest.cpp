#include <gtest/gtest.h>
#include "Ut/XCEntity/XCPoint.h"

// 测试 XCPoint 的构造函数和坐标获取方法
TEST(XCPointTest, ConstructorAndGetters) {
    XC::XCPoint point(3.0, 4.0);
    EXPECT_DOUBLE_EQ(point.x(), 3.0);
    EXPECT_DOUBLE_EQ(point.y(), 4.0);
}

// 测试 XCPoint 的加法操作符
TEST(XCPointTest, AdditionOperator) {
    XC::XCPoint point1(1.0, 2.0);
    XC::XCPoint point2(3.0, 4.0);
    XC::XCPoint result = point1 + point2;
    EXPECT_DOUBLE_EQ(result.x(), 4.0);
    EXPECT_DOUBLE_EQ(result.y(), 6.0);
}