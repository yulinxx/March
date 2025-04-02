#include <gtest/gtest.h>
#include "Ut/Vec.h"

// 测试默认构造函数
TEST(VecTest, DefaultConstructor)
{
    Ut::Vec2f vec;
    EXPECT_EQ(vec[0], 0.0f);
    EXPECT_EQ(vec[1], 0.0f);
}

// 测试二维向量构造函数
TEST(VecTest, TwoDimensionalConstructor)
{
    Ut::Vec2f vec(1.0f, 2.0f);
    EXPECT_EQ(vec[0], 1.0f);
    EXPECT_EQ(vec[1], 2.0f);
}

// 测试三维向量构造函数
TEST(VecTest, ThreeDimensionalConstructor)
{
    Ut::Vec3f vec(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(vec[0], 1.0f);
    EXPECT_EQ(vec[1], 2.0f);
    EXPECT_EQ(vec[2], 3.0f);
}

// 测试坐标访问器
TEST(VecTest, CoordinateAccessors)
{
    Ut::Vec3f vec(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(vec.x(), 1.0f);
    EXPECT_EQ(vec.y(), 2.0f);
    EXPECT_EQ(vec.z(), 3.0f);
}

// 测试坐标设置函数
TEST(VecTest, CoordinateSetters)
{
    Ut::Vec3f vec;
    vec.setX(1.0f);
    vec.setY(2.0f);
    vec.setZ(3.0f);
    EXPECT_EQ(vec.x(), 1.0f);
    EXPECT_EQ(vec.y(), 2.0f);
    EXPECT_EQ(vec.z(), 3.0f);
}

// 测试索引运算符
TEST(VecTest, IndexOperator)
{
    Ut::Vec2f vec(1.0f, 2.0f);
    EXPECT_EQ(vec[0], 1.0f);
    EXPECT_EQ(vec[1], 2.0f);
}

// 测试加法运算符
TEST(VecTest, AdditionOperator)
{
    Ut::Vec2f vec1(1.0f, 2.0f);
    Ut::Vec2f vec2(3.0f, 4.0f);
    Ut::Vec2f result = vec1 + vec2;
    EXPECT_EQ(result[0], 4.0f);
    EXPECT_EQ(result[1], 6.0f);
}

// 测试减法运算符
TEST(VecTest, SubtractionOperator)
{
    Ut::Vec2f vec1(1.0f, 2.0f);
    Ut::Vec2f vec2(3.0f, 4.0f);
    Ut::Vec2f result = vec1 - vec2;
    EXPECT_EQ(result[0], -2.0f);
    EXPECT_EQ(result[1], -2.0f);
}

// 测试标量乘法运算符
TEST(VecTest, ScalarMultiplicationOperator)
{
    Ut::Vec2f vec(1.0f, 2.0f);
    Ut::Vec2f result = vec * 2.0f;
    EXPECT_EQ(result[0], 2.0f);
    EXPECT_EQ(result[1], 4.0f);
}

// 测试标量乘法友元运算符
TEST(VecTest, ScalarMultiplicationFriendOperator)
{
    Ut::Vec2f vec(1.0f, 2.0f);
    Ut::Vec2f result = 2.0f * vec;
    EXPECT_EQ(result[0], 2.0f);
    EXPECT_EQ(result[1], 4.0f);
}

// 测试标量除法运算符
TEST(VecTest, ScalarDivisionOperator)
{
    Ut::Vec2f vec(2.0f, 4.0f);
    Ut::Vec2f result = vec / 2.0f;
    EXPECT_EQ(result[0], 1.0f);
    EXPECT_EQ(result[1], 2.0f);
}

// 测试复合加法运算符
TEST(VecTest, CompoundAdditionOperator)
{
    Ut::Vec2f vec1(1.0f, 2.0f);
    Ut::Vec2f vec2(3.0f, 4.0f);
    vec1 += vec2;
    EXPECT_EQ(vec1[0], 4.0f);
    EXPECT_EQ(vec1[1], 6.0f);
}

// 测试复合减法运算符
TEST(VecTest, CompoundSubtractionOperator)
{
    Ut::Vec2f vec1(1.0f, 2.0f);
    Ut::Vec2f vec2(3.0f, 4.0f);
    vec1 -= vec2;
    EXPECT_EQ(vec1[0], -2.0f);
    EXPECT_EQ(vec1[1], -2.0f);
}

// 测试复合标量乘法运算符
TEST(VecTest, CompoundScalarMultiplicationOperator)
{
    Ut::Vec2f vec(1.0f, 2.0f);
    vec *= 2.0f;
    EXPECT_EQ(vec[0], 2.0f);
    EXPECT_EQ(vec[1], 4.0f);
}

// 测试复合标量除法运算符
TEST(VecTest, CompoundScalarDivisionOperator)
{
    Ut::Vec2f vec(2.0f, 4.0f);
    vec /= 2.0f;
    EXPECT_EQ(vec[0], 1.0f);
    EXPECT_EQ(vec[1], 2.0f);
}

// 测试相等运算符
TEST(VecTest, EqualityOperator)
{
    Ut::Vec2f vec1(1.0f, 2.0f);
    Ut::Vec2f vec2(1.0f, 2.0f);
    EXPECT_TRUE(vec1 == vec2);
}

// 测试不等运算符
TEST(VecTest, InequalityOperator)
{
    Ut::Vec2f vec1(1.0f, 2.0f);
    Ut::Vec2f vec2(3.0f, 4.0f);
    EXPECT_TRUE(vec1 != vec2);
}

// 测试点积
TEST(VecTest, DotProduct)
{
    Ut::Vec2f vec1(1.0f, 2.0f);
    Ut::Vec2f vec2(3.0f, 4.0f);
    float dotProduct = vec1.dot(vec2);
    EXPECT_EQ(dotProduct, 11.0f);
}

// 测试叉积
TEST(VecTest, CrossProduct)
{
    Ut::Vec3f vec1(1.0f, 2.0f, 3.0f);
    Ut::Vec3f vec2(4.0f, 5.0f, 6.0f);
    Ut::Vec3f result = vec1.cross(vec2);
    EXPECT_EQ(result[0], -3.0f);
    EXPECT_EQ(result[1], 6.0f);
    EXPECT_EQ(result[2], -3.0f);
}

// 测试向量长度
TEST(VecTest, Length)
{
    Ut::Vec2f vec(3.0f, 4.0f);
    float length = vec.length();
    EXPECT_EQ(length, 5.0f);
}

// 测试向量归一化
TEST(VecTest, Normalize)
{
    Ut::Vec2f vec(3.0f, 4.0f);
    Ut::Vec2f normalized = vec.normalize();
    EXPECT_FLOAT_EQ(normalized.length(), 1.0f);
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }