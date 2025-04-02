#include <gtest/gtest.h>
#include "Ut/Matrix.h"
#include "Ut/Vec.h"

using namespace Ut;

// Test fixture for Matrix tests
class MatrixTest : public ::testing::Test
{
protected:
    Matrix<double, 3, 3> m3x3;
    Matrix<double, 4, 4> m4x4;

    void SetUp() override
    {
        m3x3.identity();
        m4x4.identity();
    }
};

// Basic construction and access tests
TEST_F(MatrixTest, ConstructionAndAccess)
{
    Matrix<double, 2, 2> m;
    EXPECT_EQ(m(0, 0), 1.0);
    EXPECT_EQ(m(0, 1), 0.0);

    Matrix<double, 2, 2> m2(2.0);
    EXPECT_EQ(m2(0, 0), 2.0);
    EXPECT_EQ(m2(1, 1), 2.0);

    EXPECT_THROW(m.at(2, 0), std::out_of_range);
}

// Arithmetic operations tests
TEST_F(MatrixTest, ArithmeticOperations)
{
    Matrix<double, 2, 2> m1(1.0);
    Matrix<double, 2, 2> m2(2.0);

    auto sum = m1 + m2;
    EXPECT_EQ(sum(0, 0), 3.0);

    auto diff = m2 - m1;
    EXPECT_EQ(diff(0, 0), 1.0);

    auto scaled = m1 * 2.0;
    EXPECT_EQ(scaled(0, 0), 2.0);
}

// Matrix multiplication tests
TEST_F(MatrixTest, MatrixMultiplication)
{
    Matrix<double, 2, 2> m1;
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;

    Matrix<double, 2, 2> m2;
    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;

    auto result = m1 * m2;
    EXPECT_EQ(result(0, 0), 19.0); // 1*5 + 2*7
    EXPECT_EQ(result(0, 1), 22.0); // 1*6 + 2*8
    EXPECT_EQ(result(1, 0), 43.0); // 3*5 + 4*7
    EXPECT_EQ(result(1, 1), 50.0); // 3*6 + 4*8
}

// Transformation tests
TEST_F(MatrixTest, Transformations)
{
    m3x3.translation(2.0, 3.0);
    EXPECT_EQ(m3x3(0, 2), 2.0);
    EXPECT_EQ(m3x3(1, 2), 3.0);

    m4x4.rotation(3.1415926 / 2); // 90 degrees
    EXPECT_NEAR(m4x4(0, 0), 0.0, 1e-6);
    EXPECT_NEAR(m4x4(0, 1), -1.0, 1e-6);
    EXPECT_NEAR(m4x4(1, 0), 1.0, 1e-6);
    EXPECT_NEAR(m4x4(1, 1), 0.0, 1e-6);

    m3x3 = Matrix<double, 3, 3>();
    m3x3.scale(2.0, 3.0);
    EXPECT_EQ(m3x3(0, 0), 2.0);
    EXPECT_EQ(m3x3(1, 1), 3.0);
}

// Linear algebra tests
TEST_F(MatrixTest, LinearAlgebra)
{
    Matrix<double, 2, 2> m;
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;

    auto trans = m.transpose();
    EXPECT_EQ(trans(0, 1), 3.0);
    EXPECT_EQ(trans(1, 0), 2.0);

    EXPECT_EQ(m.determinant(), -2.0);

    auto inv = m.inverse();
    EXPECT_NEAR(inv(0, 0), -2.0, 1e-6);
    EXPECT_NEAR(inv(0, 1), 1.0, 1e-6);
    EXPECT_NEAR(inv(1, 0), 1.5, 1e-6);
    EXPECT_NEAR(inv(1, 1), -0.5, 1e-6);
}