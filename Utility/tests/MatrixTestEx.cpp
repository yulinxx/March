#include "gtest/gtest.h"

#include "Ut/Matrix.h"
#include "Ut/Vec.h"

#include <cmath>

#include <type_traits>

#include "Ut/Matrix.h"

namespace Ut
{
    // 这里可以使用 Ut 命名空间下的类和函数
}

// // 测试代码示例
// void MatrixOutputTest_OutputStream_Test::TestBody() {
//     Ut::Matrix<double, 3, 3> mat;
//     std::ostringstream oss;
//     oss << mat; // 使用 operator<<
//     // 其他测试逻辑
// }

using namespace Ut;

namespace
{
#define TEMP_PI 3.14159265358979323846

    const double EPSILON = 1e-6;

    template<typename T>
    void expectNear(T a, T b, T epsilon = EPSILON)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            EXPECT_NEAR(a, b, epsilon);
        }
        else
        {
            EXPECT_EQ(a, b);
        }
    }

    template<typename T, size_t Rows, size_t Cols>
    void expectMatrixEqual(const Matrix<T, Rows, Cols>& a, const Matrix<T, Rows, Cols>& b)
    {
        for (size_t i = 0; i < Rows; ++i)
        {
            for (size_t j = 0; j < Cols; ++j)
            {
                expectNear(a(i, j), b(i, j));
            }
        }
    }

    // Test fixture for Matrix tests
    template<typename T>
    class MatrixTestEx : public ::testing::Test
    {
    protected:
        using Matrix3 = Matrix<T, 3, 3>;
        using Matrix4 = Matrix<T, 4, 4>;
        using Vec2 = Vec<T, 2>;
        using Vec3 = Vec<T, 3>;
        using Vec4 = Vec<T, 4>;

        void SetUp() override
        {
            // Initialize test matrices
            mat3x3_1 = {
                1, 2, 3,
                4, 5, 6,
                7, 8, 9
            };

            mat3x3_2 = {
                9, 8, 7,
                6, 5, 4,
                3, 2, 1
            };

            mat4x4_1 = {
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16
            };

            mat4x4_2 = {
                16, 15, 14, 13,
                12, 11, 10, 9,
                8, 7, 6, 5,
                4, 3, 2, 1
            };

            identity3x3 = Matrix3();
            identity3x3.identity();

            identity4x4 = Matrix4();
            identity4x4.identity();
        }

        Matrix3 mat3x3_1;
        Matrix3 mat3x3_2;
        Matrix3 identity3x3;
        Matrix4 mat4x4_1;
        Matrix4 mat4x4_2;
        Matrix4 identity4x4;
    };

    using TestTypes = ::testing::Types<float, double>;
    TYPED_TEST_SUITE(MatrixTestEx, TestTypes);

    // Constructor tests
    TYPED_TEST(MatrixTestEx, DefaultConstructor)
    {
        // 单位矩阵
        typename TestFixture::Matrix3 m;
        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                TypeParam expected = (i == j) ? TypeParam(1) : TypeParam(0);
                expectNear(m(i, j), expected);
            }
        }
    }

    TYPED_TEST(MatrixTestEx, ValueConstructor)
    {
        TypeParam value = 5;
        typename TestFixture::Matrix3 m(value);
        for (size_t i = 0; i < 3; ++i)
        {
            for (size_t j = 0; j < 3; ++j)
            {
                expectNear(m(i, j), value);
            }
        }
    }

    // Accessor tests
    TYPED_TEST(MatrixTestEx, AtAccessor)
    {
        EXPECT_NO_THROW(this->mat3x3_1.at(0, 0));
        EXPECT_NO_THROW(this->mat3x3_1.at(2, 2));
        EXPECT_THROW(this->mat3x3_1.at(3, 0), std::out_of_range);
        EXPECT_THROW(this->mat3x3_1.at(0, 3), std::out_of_range);

        expectNear(this->mat3x3_1.at(1, 1), TypeParam(5));
    }

    TYPED_TEST(MatrixTestEx, ParenthesesAccessor)
    {
        expectNear(this->mat3x3_1(0, 0), TypeParam(1));
        expectNear(this->mat3x3_1(1, 2), TypeParam(6));
        expectNear(this->mat3x3_1(2, 1), TypeParam(8));
    }

    // Arithmetic operator tests
    TYPED_TEST(MatrixTestEx, MatrixAddition)
    {
        auto result = this->mat3x3_1 + this->mat3x3_2;
        typename TestFixture::Matrix3 expected{
            10, 10, 10,
            10, 10, 10,
            10, 10, 10
        };
        expectMatrixEqual(result, expected);
    }

    TYPED_TEST(MatrixTestEx, MatrixSubtraction)
    {
        auto result = this->mat3x3_1 - this->mat3x3_2;
        typename TestFixture::Matrix3 expected{
            -8, -6, -4,
            -2, 0, 2,
            4, 6, 8
        };
        expectMatrixEqual(result, expected);
    }

    TYPED_TEST(MatrixTestEx, ScalarMultiplication)
    {
        TypeParam scalar = 2;
        auto result = this->mat3x3_1 * scalar;
        typename TestFixture::Matrix3 expected{
            2, 4, 6,
            8, 10, 12,
            14, 16, 18
        };
        expectMatrixEqual(result, expected);
    }

    TYPED_TEST(MatrixTestEx, MatrixMultiplication)
    {
        typename TestFixture::Matrix3 a{
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        };
        typename TestFixture::Matrix3 b{
            9, 8, 7,
            6, 5, 4,
            3, 2, 1
        };
        auto result = a * b;
        typename TestFixture::Matrix3 expected{
            30, 24, 18,
            84, 69, 54,
            138, 114, 90
        };
        expectMatrixEqual(result, expected);
    }

    TYPED_TEST(MatrixTestEx, MatrixVectorMultiplication)
    {
        typename TestFixture::Vec3 v{ 1, 2, 3 };
        auto result = this->mat3x3_1 * v;
        typename TestFixture::Vec3 expected{ 14, 32, 50 };
        for (size_t i = 0; i < 3; ++i)
        {
            expectNear(result[i], expected[i]);
        }
    }

    TYPED_TEST(MatrixTestEx, MatrixMultiplicationAssignment)
    {
        typename TestFixture::Matrix3 a{
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        };
        typename TestFixture::Matrix3 b{
            9, 8, 7,
            6, 5, 4,
            3, 2, 1
        };
        a *= b;
        typename TestFixture::Matrix3 expected{
            30, 24, 18,
            84, 69, 54,
            138, 114, 90
        };
        expectMatrixEqual(a, expected);
    }

    // Transformation tests
    TYPED_TEST(MatrixTestEx, Identity)
    {
        typename TestFixture::Matrix3 m;
        m.identity();
        expectMatrixEqual(m, this->identity3x3);
    }

    TYPED_TEST(MatrixTestEx, Translation)
    {
        typename TestFixture::Matrix3 m;
        m.translation(TypeParam(2), TypeParam(3));

        typename TestFixture::Matrix3 expected{
            1, 0, 2,
            0, 1, 3,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, TranslationWithVec)
    {
        typename TestFixture::Vec2 v(TypeParam(2), TypeParam(3));
        typename TestFixture::Matrix3 m;
        m.translation(v);

        typename TestFixture::Matrix3 expected{
            1, 0, 2,
            0, 1, 3,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, Rotation)
    {
        typename TestFixture::Matrix3 m;
        TypeParam angle = float(TEMP_PI / 2.0); // 90 degrees
        m.rotation(angle);

        typename TestFixture::Matrix3 expected{
            cos(angle), -sin(angle), 0,
            sin(angle), cos(angle), 0,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, Scale)
    {
        typename TestFixture::Matrix3 m;
        m.scale(TypeParam(2), TypeParam(3));

        typename TestFixture::Matrix3 expected{
            2, 0, 0,
            0, 3, 0,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, ScaleWithVec)
    {
        typename TestFixture::Vec2 v(TypeParam(2), TypeParam(3));
        typename TestFixture::Matrix3 m;
        m.scale(v);

        typename TestFixture::Matrix3 expected{
            2, 0, 0,
            0, 3, 0,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, ScaleWithCenter)
    {
        typename TestFixture::Matrix3 m;
        m.scale(TypeParam(2), TypeParam(3), TypeParam(1), TypeParam(1));

        // Expected matrix for scaling by (2,3) about (1,1)
        typename TestFixture::Matrix3 expected{
            2, 0, -1,
            0, 3, -2,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, UniformScale)
    {
        typename TestFixture::Matrix3 m;
        m.scale(TypeParam(2));

        typename TestFixture::Matrix3 expected{
            2, 0, 0,
            0, 2, 0,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, UniformScaleWithCenter)
    {
        typename TestFixture::Matrix3 m;
        m.scale(TypeParam(2), TypeParam(1), TypeParam(1));

        // Expected matrix for scaling by 2 about (1,1)
        typename TestFixture::Matrix3 expected{
            2, 0, -1,
            0, 2, -1,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, MirrorX)
    {
        typename TestFixture::Matrix3 m;
        m.mirrorX();

        typename TestFixture::Matrix3 expected{
            -1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, MirrorY)
    {
        typename TestFixture::Matrix3 m;
        m.mirrorY();

        typename TestFixture::Matrix3 expected{
            1, 0, 0,
            0, -1, 0,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, MirrorXY)
    {
        typename TestFixture::Matrix3 m;
        m.mirrorXY();

        typename TestFixture::Matrix3 expected{
            -1, 0, 0,
            0, -1, 0,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, TranslateAndScale)
    {
        typename TestFixture::Matrix3 m;
        m.translateAndScale(TypeParam(1), TypeParam(2), TypeParam(3), TypeParam(4));

        // Expected matrix: translation followed by scaling
        typename TestFixture::Matrix3 expected{
            3, 0, 1,
            0, 4, 2,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, Ortho2D)
    {
        typename TestFixture::Matrix3 m;
        m.ortho2D(TypeParam(0), TypeParam(800), TypeParam(0), TypeParam(600));

        // Expected orthographic projection matrix
        typename TestFixture::Matrix3 expected{
            TypeParam(2.0 / 800), 0, -1,
            0, TypeParam(2.0 / 600), -1,
            0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    TYPED_TEST(MatrixTestEx, Ortho)
    {
        typename TestFixture::Matrix4 m;
        m.ortho(TypeParam(0), TypeParam(800), TypeParam(0), TypeParam(600), TypeParam(-1), TypeParam(1));

        // Expected orthographic projection matrix
        typename TestFixture::Matrix4 expected{
            TypeParam(2.0 / 800), 0, 0, -1,
            0, TypeParam(2.0 / 600), 0, -1,
            0, 0, -1, 0,
            0, 0, 0, 1
        };
        expectMatrixEqual(m, expected);

        double left = 0.0, right = 800.0;
        double bottom = 0.0, top = 600.0;
        double near = -1.0, far = 1.0;

        Ut::Mat4 mat;
        mat.identity();
        mat(0, 0) = 2 / (right - left);
        mat(1, 1) = 2 / (top - bottom);
        mat(2, 2) = -2 / (far - near);
        mat(0, 3) = -(right + left) / (right - left);
        mat(1, 3) = -(top + bottom) / (top - bottom);
        mat(2, 3) = -(far + near) / (far - near);

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                EXPECT_NEAR(mat(i, j), m(i, j), 1e-6);
            }
        }
    }

    TYPED_TEST(MatrixTestEx, OrthoWithoutNearFar)
    {
        typename TestFixture::Matrix4 m;
        m.ortho(TypeParam(0), TypeParam(800), TypeParam(0), TypeParam(600));

        // Expected orthographic projection matrix with default near/far
        typename TestFixture::Matrix4 expected{
            TypeParam(2.0 / 800), 0, 0, -1,
            0, TypeParam(2.0 / 600), 0, -1,
            0, 0, -1, 0,
            0, 0, 0, 1
        };
        expectMatrixEqual(m, expected);
    }

    // Matrix operations tests
    TYPED_TEST(MatrixTestEx, Transpose)
    {
        auto transposed = this->mat3x3_1.transpose();
        typename TestFixture::Matrix3 expected{
            1, 4, 7,
            2, 5, 8,
            3, 6, 9
        };
        expectMatrixEqual(transposed, expected);
    }

    TYPED_TEST(MatrixTestEx, Determinant)
    {
        typename TestFixture::Matrix3 m{
            1, 2, 3,
            0, 1, 4,
            5, 6, 0
        };
        expectNear(m.determinant(), TypeParam(1));
    }

    TYPED_TEST(MatrixTestEx, Inverse)
    {
        typename TestFixture::Matrix3 m{
            1, 2, 3,
            0, 1, 4,
            5, 6, 0
        };
        auto inv = m.inverse();

        // Expected inverse
        typename TestFixture::Matrix3 expected{
            -24, 18, 5,
            20, -15, -4,
            -5, 4, 1
        };
        expectMatrixEqual(inv, expected);

        // Verify that m * inv is identity
        auto product = m * inv;
        expectMatrixEqual(product, this->identity3x3);
    }

    // Test 2x2 matrix inverse
    TYPED_TEST(MatrixTestEx, Inverse2x2)
    {
        Matrix<double, 2, 2> mat({ 1, 2, 3, 4 });
        try
        {
            Matrix<double, 2, 2> inv = mat.inverse();
            Matrix<double, 2, 2> product = mat * inv;
            // Check if the result is close to the identity matrix
            for (size_t i = 0; i < 2; ++i)
            {
                for (size_t j = 0; j < 2; ++j)
                {
                    if (i == j)
                    {
                        EXPECT_NEAR(product(i, j), 1.0, 1e-4);
                    }
                    else
                    {
                        EXPECT_NEAR(product(i, j), 0.0, 1e-4);
                    }
                }
            }
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << "Exception thrown: " << e.what();
        }
    }

    // Test 3x3 matrix inverse
    TYPED_TEST(MatrixTestEx, Inverse3x3)
    {
        Matrix<double, 3, 3> mat({ 1, 2, 3, 4, 5, 6, 7, 8, 10 });
        try
        {
            Matrix<double, 3, 3> inv = mat.inverse();
            Matrix<double, 3, 3> product = mat * inv;
            // Check if the result is close to the identity matrix
            for (size_t i = 0; i < 3; ++i)
            {
                for (size_t j = 0; j < 3; ++j)
                {
                    if (i == j)
                    {
                        EXPECT_NEAR(product(i, j), 1.0, 1e-4);
                    }
                    else
                    {
                        EXPECT_NEAR(product(i, j), 0.0, 1e-4);
                    }
                }
            }
        }
        catch (const std::runtime_error& e)
        {
            FAIL() << "Exception thrown: " << e.what();
        }
    }

    //// 测试 2x2 矩阵求逆
    //TEST(MatrixTest, Inverse2x2)
    //{
    //    //Matrix<double, 2, 2> mat = { 1, 2, 3, 4 };
    //    Matrix<double, 2, 2> mat({ 1, 2, 3, 4 });

    //    try
    //    {
    //        Matrix<double, 2, 2> inv = mat.inverse();
    //        Matrix<double, 2, 2> product = mat * inv;
    //        // 检查结果是否接近单位矩阵
    //        for (size_t i = 0; i < 2; ++i)
    //        {
    //            for (size_t j = 0; j < 2; ++j)
    //            {
    //                if (i == j)
    //                {
    //                    EXPECT_NEAR(product(i, j), 1.0, 1e-6);
    //                }
    //                else
    //                {
    //                    EXPECT_NEAR(product(i, j), 0.0, 1e-6);
    //                }
    //            }
    //        }
    //    }
    //    catch (const std::runtime_error& e)
    //    {
    //        FAIL() << "Exception thrown: " << e.what();
    //    }
    //}

    //// 测试 3x3 矩阵求逆
    //TEST(MatrixTest, Inverse3x3)
    //{
    //    //Matrix<double, 3, 3> mat = { 1, 2, 3, 4, 5, 6, 7, 8, 10 };
    //    Matrix<double, 3, 3> mat({ 1, 2, 3, 4, 5, 6, 7, 8, 10 });

    //    try
    //    {
    //        Matrix<double, 3, 3> inv = mat.inverse();
    //        Matrix<double, 3, 3> product = mat * inv;
    //        // 检查结果是否接近单位矩阵
    //        for (size_t i = 0; i < 3; ++i)
    //        {
    //            for (size_t j = 0; j < 3; ++j)
    //            {
    //                if (i == j)
    //                {
    //                    EXPECT_NEAR(product(i, j), 1.0, 1e-6);
    //                }
    //                else
    //                {
    //                    EXPECT_NEAR(product(i, j), 0.0, 1e-6);
    //                }
    //            }
    //        }
    //    }
    //    catch (const std::runtime_error& e)
    //    {
    //        FAIL() << "Exception thrown: " << e.what();
    //    }
    //}

    // 测试 4x4 矩阵求逆
    //TEST(MatrixTest, Inverse4x4)
    //{
    //    //Matrix<double, 4, 4> mat = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

    //    //Matrix<double, 4, 4> mat;
    //    Matrix<double, 4, 4> mat({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    //    //mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3; mat(0, 3) = 4;
    //    //mat(1, 0) = 5; mat(1, 1) = 6; mat(1, 2) = 7; mat(1, 3) = 8;

    //    //mat(2, 0) = 9; mat(2, 1) = 10; mat(2, 2) = 11; mat(2, 3) = 12;
    //    //mat(3, 0) = 13; mat(3, 1) = 14; mat(3, 2) = 15; mat(3, 3) = 16;

    //    try
    //    {
    //        Matrix<double, 4, 4> inv = mat.inverse();
    //        Matrix<double, 4, 4> product = mat * inv;
    //        // 检查结果是否接近单位矩阵
    //        for (size_t i = 0; i < 4; ++i)
    //        {
    //            for (size_t j = 0; j < 4; ++j)
    //            {
    //                if (i == j)
    //                {
    //                    EXPECT_NEAR(product(i, j), 1.0, 1e-6);
    //                }
    //                else
    //                {
    //                    EXPECT_NEAR(product(i, j), 0.0, 1e-6);
    //                }
    //            }
    //        }
    //    }
    //    catch (const std::runtime_error& e)
    //    {
    //        FAIL() << "Exception thrown: " << e.what();
    //    }
    //}

    // Output stream test
    // TEST(MatrixOutputTest, OutputStream)
    // {
    //     Matrix3d m{
    //         1, 2, 3,
    //         4, 5, 6,
    //         7, 8, 9
    //     };

    //     std::ostringstream oss;
    //     oss << m;

    //     std::string expected = "1 2 3 \n4 5 6 \n7 8 9 \n";
    //     EXPECT_EQ(oss.str(), expected);
    // }
}