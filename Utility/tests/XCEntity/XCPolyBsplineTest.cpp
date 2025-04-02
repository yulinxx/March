#include <gtest/gtest.h>
#include "Ut/XCEntity/XCPolyBspline.h"

// 测试 XCPolyBspline 的构造函数
TEST(XCPolyBsplineTest, Constructor) {
    XC::XCPolyBspline spline;
    // 可以根据构造函数的行为添加断言，例如检查初始状态下的某些属性
    EXPECT_EQ(spline.controlPoints().size(), 0);
}

// 测试添加控制点
TEST(XCPolyBsplineTest, AddControlPoint) {
    XC::XCPolyBspline spline;
    XC::XCPoint point(1.0, 2.0);
    spline.addControlPoint(point);
    EXPECT_EQ(spline.controlPoints().size(), 1);
    EXPECT_EQ(spline.controlPoints()[0].x(), point.x());
    EXPECT_EQ(spline.controlPoints()[0].y(), point.y());
}

// 测试曲线计算
TEST(XCPolyBsplineTest, CurveEvaluation) {
    XC::XCPolyBspline spline;
    // 添加一些控制点
    spline.addControlPoint(XC::XCPoint(0.0, 0.0));
    spline.addControlPoint(XC::XCPoint(1.0, 1.0));
    spline.addControlPoint(XC::XCPoint(2.0, 2.0));

    // 计算曲线在某个参数位置的值
    XC::XCPoint result = spline.evaluate(0.5);
    // 可以根据具体的曲线计算逻辑添加更准确的断言
    EXPECT_FALSE(result.isNull());
}

// 测试获取控制点数量
TEST(XCPolyBsplineTest, ControlPointCount) {
    XC::XCPolyBspline spline;
    spline.addControlPoint(XC::XCPoint(0.0, 0.0));
    spline.addControlPoint(XC::XCPoint(1.0, 1.0));
    EXPECT_EQ(spline.controlPointCount(), 2);
}