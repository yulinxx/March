#include <gtest/gtest.h>
#include "Ut/XCEntity/XCPolyLine.h"

// Test the constructor of XCPolyLine
TEST(XCPolyLineTest, Constructor) {
    XC::XCPolyLine polyline;
    EXPECT_EQ(polyline.vertexCount(), 0);
}

// Test adding vertices to the polyline
TEST(XCPolyLineTest, AddVertex) {
    XC::XCPolyLine polyline;
    XC::XCPoint point(1.0, 2.0);
    polyline.addVertex(point);
    EXPECT_EQ(polyline.vertexCount(), 1);
    EXPECT_EQ(polyline.vertex(0).x(), point.x());
    EXPECT_EQ(polyline.vertex(0).y(), point.y());
}

// Test calculating the length of the polyline
TEST(XCPolyLineTest, CalculateLength) {
    XC::XCPolyLine polyline;
    polyline.addVertex(XC::XCPoint(0.0, 0.0));
    polyline.addVertex(XC::XCPoint(3.0, 0.0));
    polyline.addVertex(XC::XCPoint(3.0, 4.0));
    double length = polyline.calculateLength();
    EXPECT_DOUBLE_EQ(length, 7.0);
}