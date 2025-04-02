#include "Ut/Vec.h"
#include <gtest/gtest.h>

namespace Ut
{
    // Helper function to create a Vec from an initializer list
    template <typename T, size_t N>
    Vec<T, N> makeVec(const std::initializer_list<T>& list)
    {
        return Vec<T, N>(list.begin(), list.end());
    }
}

using namespace Ut;

// Test fixture for Vec
template <typename T, size_t N>
class VecTest : public ::testing::Test
{
protected:
    Vec<T, N> zeroVec;
    Vec<T, N> oneVec;
    Vec<T, N> randomVec;

    VecTest()
        : zeroVec(), oneVec(T(1)), randomVec()
    {
        // 动态初始化 randomVec
        for (size_t i = 0; i < N; ++i)
        {
            randomVec[i] = static_cast<T>(i + 1);  // 使用 1, 2, 3, ... 来初始化
        }
    }
};

// Test cases for Vec2
typedef VecTest<float, 2> Vec2fTest;
typedef VecTest<double, 2> Vec2dTest;
typedef VecTest<int, 2> Vec2iTest;

// Test cases for Vec3
typedef VecTest<float, 3> Vec3fTest;
typedef VecTest<double, 3> Vec3dTest;
typedef VecTest<int, 3> Vec3iTest;

// Test cases for Vec2
TEST_F(Vec2fTest, DefaultConstructor)
{
    EXPECT_EQ(zeroVec.x(), 0.0f);
    EXPECT_EQ(zeroVec.y(), 0.0f);
}

TEST_F(Vec2fTest, UniformConstructor)
{
    EXPECT_EQ(oneVec.x(), 1.0f);
    EXPECT_EQ(oneVec.y(), 1.0f);
}

TEST_F(Vec2fTest, SpecificConstructor)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    EXPECT_EQ(vec.x(), 2.0f);
    EXPECT_EQ(vec.y(), 3.0f);
}

TEST_F(Vec2fTest, Accessors)
{
    EXPECT_EQ(zeroVec[0], 0.0f);
    EXPECT_EQ(zeroVec[1], 0.0f);
}

TEST_F(Vec2fTest, Setters)
{
    zeroVec.setX(5.0f);
    zeroVec.setY(7.0f);
    EXPECT_EQ(zeroVec.x(), 5.0f);
    EXPECT_EQ(zeroVec.y(), 7.0f);
}

TEST_F(Vec2fTest, Addition)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> other(4.0f, 5.0f);
    Vec<float, 2> result = vec + other;
    EXPECT_EQ(result.x(), 6.0f);
    EXPECT_EQ(result.y(), 8.0f);
}

TEST_F(Vec2fTest, Subtraction)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> other(4.0f, 5.0f);
    Vec<float, 2> result = vec - other;
    EXPECT_EQ(result.x(), -2.0f);
    EXPECT_EQ(result.y(), -2.0f);
}

TEST_F(Vec2fTest, ScalarMultiplication)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> result = vec * 2.0f;
    EXPECT_EQ(result.x(), 4.0f);
    EXPECT_EQ(result.y(), 6.0f);
}

TEST_F(Vec2fTest, ScalarDivision)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> result = vec / 2.0f;
    EXPECT_EQ(result.x(), 1.0f);
    EXPECT_EQ(result.y(), 1.5f);
}

TEST_F(Vec2fTest, DotProduct)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> other(4.0f, 5.0f);
    EXPECT_EQ(vec.dot(other), 23.0f);
}

TEST_F(Vec2fTest, LengthSquared)
{
    Vec<float, 2> vec(3.0f, 4.0f);
    EXPECT_EQ(vec.lengthSquared(), 25.0f);
}

TEST_F(Vec2fTest, Length)
{
    Vec<float, 2> vec(3.0f, 4.0f);
    EXPECT_NEAR(vec.length(), 5.0f, 1e-6);
}

TEST_F(Vec2fTest, Normalize)
{
    Vec<float, 2> vec(3.0f, 4.0f);
    Vec<float, 2> normalized = vec.normalize();
    EXPECT_NEAR(normalized.length(), 1.0f, 1e-6);
}

TEST_F(Vec2fTest, IsZero)
{
    Vec<float, 2> vec(0.0f, 0.0f);
    EXPECT_TRUE(vec.isZero());
}

TEST_F(Vec2fTest, NotZero)
{
    Vec<float, 2> vec(0.001f, 0.00001f);
    EXPECT_FALSE(vec.isZero());
}

TEST_F(Vec2fTest, Equality)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> other(2.0f, 3.0f);
    EXPECT_TRUE(vec == other);
}

TEST_F(Vec2fTest, Inequality)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> other(4.0f, 5.0f);
    EXPECT_TRUE(vec != other);
}

TEST_F(Vec2fTest, Distance)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> other(4.0f, 5.0f);
    EXPECT_NEAR(vec.distance(other), std::sqrt(8.0f), 1e-6);
}

TEST_F(Vec2fTest, Lerp)
{
    Vec<float, 2> vec(2.0f, 3.0f);
    Vec<float, 2> other(4.0f, 5.0f);
    Vec<float, 2> result = Vec<float, 2>::lerp(vec, other, 0.5f);
    EXPECT_EQ(result.x(), 3.0f);
    EXPECT_EQ(result.y(), 4.0f);
}

// Test cases for Vec3
TEST_F(Vec3fTest, DefaultConstructor)
{
    EXPECT_EQ(zeroVec.x(), 0.0f);
    EXPECT_EQ(zeroVec.y(), 0.0f);
    EXPECT_EQ(zeroVec.z(), 0.0f);
}

TEST_F(Vec3fTest, UniformConstructor)
{
    EXPECT_EQ(oneVec.x(), 1.0f);
    EXPECT_EQ(oneVec.y(), 1.0f);
    EXPECT_EQ(oneVec.z(), 1.0f);
}

TEST_F(Vec3fTest, SpecificConstructor)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    EXPECT_EQ(vec.x(), 2.0f);
    EXPECT_EQ(vec.y(), 3.0f);
    EXPECT_EQ(vec.z(), 4.0f);
}

TEST_F(Vec3fTest, Accessors)
{
    EXPECT_EQ(zeroVec[0], 0.0f);
    EXPECT_EQ(zeroVec[1], 0.0f);
    EXPECT_EQ(zeroVec[2], 0.0f);
}

TEST_F(Vec3fTest, Setters)
{
    zeroVec.setX(5.0f);
    zeroVec.setY(7.0f);
    zeroVec.setZ(9.0f);
    EXPECT_EQ(zeroVec.x(), 5.0f);
    EXPECT_EQ(zeroVec.y(), 7.0f);
    EXPECT_EQ(zeroVec.z(), 9.0f);
}

TEST_F(Vec3fTest, Addition)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(4.0f, 5.0f, 6.0f);
    Vec<float, 3> result = vec + other;
    EXPECT_EQ(result.x(), 6.0f);
    EXPECT_EQ(result.y(), 8.0f);
    EXPECT_EQ(result.z(), 10.0f);
}

TEST_F(Vec3fTest, Subtraction)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(4.0f, 5.0f, 6.0f);
    Vec<float, 3> result = vec - other;
    EXPECT_EQ(result.x(), -2.0f);
    EXPECT_EQ(result.y(), -2.0f);
    EXPECT_EQ(result.z(), -2.0f);
}

TEST_F(Vec3fTest, ScalarMultiplication)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> result = vec * 2.0f;
    EXPECT_EQ(result.x(), 4.0f);
    EXPECT_EQ(result.y(), 6.0f);
    EXPECT_EQ(result.z(), 8.0f);
}

TEST_F(Vec3fTest, ScalarDivision)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> result = vec / 2.0f;
    EXPECT_EQ(result.x(), 1.0f);
    EXPECT_EQ(result.y(), 1.5f);
    EXPECT_EQ(result.z(), 2.0f);
}

TEST_F(Vec3fTest, DotProduct)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(4.0f, 5.0f, 6.0f);
    EXPECT_EQ(vec.dot(other), 47.0f);
}

TEST_F(Vec3fTest, CrossProduct)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(4.0f, 5.0f, 6.0f);
    Vec<float, 3> result = vec.cross(other);
    EXPECT_EQ(result.x(), -2.0f);
    EXPECT_EQ(result.y(), 4.0f);
    EXPECT_EQ(result.z(), -2.0f);
}

TEST_F(Vec3fTest, LengthSquared)
{
    Vec<float, 3> vec(3.0f, 4.0f, 5.0f);
    EXPECT_EQ(vec.lengthSquared(), 50.0f);
}

TEST_F(Vec3fTest, Length)
{
    Vec<float, 3> vec(3.0f, 4.0f, 5.0f);
    EXPECT_NEAR(vec.length(), std::sqrt(50.0f), 1e-6);
}

TEST_F(Vec3fTest, Normalize)
{
    Vec<float, 3> vec(3.0f, 4.0f, 5.0f);
    Vec<float, 3> normalized = vec.normalize();
    EXPECT_NEAR(normalized.length(), 1.0f, 1e-6);
}

TEST_F(Vec3fTest, IsZero)
{
    Vec<float, 3> vec(0.0f, 0.0f, 0.0f);
    EXPECT_TRUE(vec.isZero());
}

TEST_F(Vec3fTest, NotZero)
{
    Vec<float, 3> vec(0.001f, 0.000f, 0.00001f);
    EXPECT_FALSE(vec.isZero());
}

TEST_F(Vec3fTest, Equality)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(2.0f, 3.0f, 4.0f);
    EXPECT_TRUE(vec == other);
}

TEST_F(Vec3fTest, Inequality)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(vec != other);
}

TEST_F(Vec3fTest, Distance)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(4.0f, 5.0f, 6.0f);
    EXPECT_NEAR(vec.distance(other), std::sqrt(12.0f), 1e-6);
}

TEST_F(Vec3fTest, Lerp)
{
    Vec<float, 3> vec(2.0f, 3.0f, 4.0f);
    Vec<float, 3> other(4.0f, 5.0f, 6.0f);
    Vec<float, 3> result = Vec<float, 3>::lerp(vec, other, 0.5f);
    EXPECT_EQ(result.x(), 3.0f);
    EXPECT_EQ(result.y(), 4.0f);
    EXPECT_EQ(result.z(), 5.0f);
}

// int main(int argc, char** argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }