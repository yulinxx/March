// #include <gtest/gtest.h>
// #include "Ut/Rect.h"
// #include "Ut/Vec.h"

// // 测试 Rect 类
// template <typename T, int DIM>
// class RectTest : public ::testing::Test {};

// TYPED_TEST_SUITE_P(RectTest);

// TYPED_TEST_P(RectTest, DefaultConstructor) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     RectType rect;
//     EXPECT_EQ(rect.min(), Ut::Vec<TypeParam, 2>());
//     EXPECT_EQ(rect.max(), Ut::Vec<TypeParam, 2>());
// }

// TYPED_TEST_P(RectTest, ParameterizedConstructor) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min(1, 1);
//     Ut::Vec<TypeParam, 2> max(2, 2);
//     RectType rect(min, max);
//     EXPECT_EQ(rect.min(), min);
//     EXPECT_EQ(rect.max(), max);
// }

// TYPED_TEST_P(RectTest, EqualityOperators) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min(1, 1);
//     Ut::Vec<TypeParam, 2> max(2, 2);
//     RectType rect1(min, max);
//     RectType rect2(min, max);
//     RectType rect3(Ut::Vec<TypeParam, 2>(3, 3), Ut::Vec<TypeParam, 2>(4, 4));
//     EXPECT_EQ(rect1, rect2);
//     EXPECT_NE(rect1, rect3);
// }

// TYPED_TEST_P(RectTest, Merge) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min1(1, 1);
//     Ut::Vec<TypeParam, 2> max1(2, 2);
//     Ut::Vec<TypeParam, 2> min2(0, 0);
//     Ut::Vec<TypeParam, 2> max2(3, 3);
//     RectType rect1(min1, max1);
//     RectType rect2(min2, max2);
//     rect1.merge(rect2);
//     EXPECT_EQ(rect1.min(), min2);
//     EXPECT_EQ(rect1.max(), max2);
// }

// TYPED_TEST_P(RectTest, Area) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min(1, 1);
//     Ut::Vec<TypeParam, 2> max(3, 3);
//     RectType rect(min, max);
//     EXPECT_EQ(rect.area(), (max.x() - min.x()) * (max.y() - min.y()));
// }

// TYPED_TEST_P(RectTest, Intersects) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min1(1, 1);
//     Ut::Vec<TypeParam, 2> max1(2, 2);
//     Ut::Vec<TypeParam, 2> min2(1.5, 1.5);
//     Ut::Vec<TypeParam, 2> max2(2.5, 2.5);
//     RectType rect1(min1, max1);
//     RectType rect2(min2, max2);
//     EXPECT_TRUE(rect1.intersects(rect2));
// }

// TYPED_TEST_P(RectTest, ContainsPoint) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min(1, 1);
//     Ut::Vec<TypeParam, 2> max(2, 2);
//     RectType rect(min, max);
//     Ut::Vec<TypeParam, 2> point(1.5, 1.5);
//     EXPECT_TRUE(rect.contains(point));
// }

// TYPED_TEST_P(RectTest, ContainsRect) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min1(1, 1);
//     Ut::Vec<TypeParam, 2> max1(3, 3);
//     Ut::Vec<TypeParam, 2> min2(1.5, 1.5);
//     Ut::Vec<TypeParam, 2> max2(2.5, 2.5);
//     RectType rect1(min1, max1);
//     RectType rect2(min2, max2);
//     EXPECT_TRUE(rect1.contains(rect2));
// }

// TYPED_TEST_P(RectTest, GetCenter) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min(1, 1);
//     Ut::Vec<TypeParam, 2> max(3, 3);
//     RectType rect(min, max);
//     Ut::Vec<TypeParam, 2> center = rect.getCenter();
//     EXPECT_EQ(center, (min + max) * TypeParam(0.5));
// }

// TYPED_TEST_P(RectTest, GetSize) {
//     using RectType = Ut::Rect<TypeParam, 2>;
//     Ut::Vec<TypeParam, 2> min(1, 1);
//     Ut::Vec<TypeParam, 2> max(3, 3);
//     RectType rect(min, max);
//     Ut::Vec<TypeParam, 2> size = rect.getSize();
//     EXPECT_EQ(size, max - min);
// }

// REGISTER_TYPED_TEST_SUITE_P(RectTest,
//                             DefaultConstructor,
//                             ParameterizedConstructor,
//                             EqualityOperators,
//                             Merge,
//                             Area,
//                             Intersects,
//                             ContainsPoint,
//                             ContainsRect,
//                             GetCenter,
//                             GetSize);

// using MyTypes = ::testing::Types<int, float, double>;
// INSTANTIATE_TYPED_TEST_SUITE_P(My, RectTest, MyTypes);

// // 测试 AxisAlignedBoundingBox 类
// TEST(AxisAlignedBoundingBoxTest, Constructor) {
//     Ut::Vec2d min(1, 1);
//     Ut::Vec2d max(2, 2);
//     Ut::AxisAlignedBoundingBox aabb(min, max);
//     EXPECT_EQ(aabb.getMinPt(), min);
//     EXPECT_EQ(aabb.getMaxPt(), max);
// }

// // 测试 TightBoundingBox 类
// TEST(TightBoundingBoxTest, ComputeFromPoints) {
//     std::vector<Ut::Vec2d> points = {Ut::Vec2d(1, 1), Ut::Vec2d(2, 2)};
//     Ut::TightBoundingBox tbb;
//     tbb.computeFromPoints(points);
//     // 这里需要根据 computeFromPoints 的具体实现来验证结果
// }

// // int main(int argc, char **argv) {
// //     ::testing::InitGoogleTest(&argc, argv);
// //     return RUN_ALL_TESTS();
// // }