#ifndef MATRIX_H
#define MATRIX_H

#include "Vec.h"
#include "UtilityAPI.h"
#include <iostream>
#include <array>
#include <stdexcept>
#include <initializer_list>

namespace Ut
{
    template <typename T, size_t Rows, size_t Cols>
    class UTILITY_API Matrix
    {
        static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

    public:
        Matrix() noexcept;
        explicit Matrix(T value) noexcept;
        explicit Matrix(std::initializer_list<T> init);

        T& at(size_t row, size_t col);
        const T& at(size_t row, size_t col) const;
        T& operator()(size_t row, size_t col);
        const T& operator()(size_t row, size_t col) const;

        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(T scalar) const;
        Matrix& operator*=(const Matrix& other);
        Matrix& operator=(std::initializer_list<T> init);

        template<size_t OtherCols>
        Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Cols, OtherCols>& other) const;

        Vec<T, Rows> operator*(const Vec<T, Cols>& vec) const;

        // Transformation methods
        void identity() requires (Rows == Cols);

        void translation(T x, T y) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void translation(const Vec<T, 2>& v) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);

        Vec<T, 2> transformPoint(const Vec<T, 2>& point) const requires (Rows == 3 && Cols == 3);

        void rotation(T angle) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void rotation(T angle, T centerX, T centerY) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void rotation(T angle, const Vec<T, 2>& pt) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);

        void scale(T sx, T sy) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void scale(const Vec<T, 2>& s) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void scale(T sx, T sy, T centerX, T centerY) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void scale(const Vec<T, 2>& s, const Vec<T, 2>& center) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void scale(T s) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void scale(T s, T centerX, T centerY) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);

        void mirrorX() requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void mirrorY() requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void mirrorXY() requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);

        void translateAndScale(T tx, T ty, T sx, T sy) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);
        void translateAndScale(const Vec<T, 2>& translation, const Vec<T, 2>& scale) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3);

        void ortho2D(T left, T right, T bottom, T top) requires (Rows == 3 && Cols == 3);
        void ortho(T left, T right, T bottom, T top, T near, T far) requires (Rows == 4 && Cols == 4);
        void ortho(T left, T right, T bottom, T top) requires (Rows == 4 && Cols == 4);

        Matrix<T, Cols, Rows> transpose() const;
        T determinant() const requires (Rows == Cols);
        Matrix inverse() const requires (Rows == Cols);

    private:
        std::array<T, Rows* Cols> data;

    public:
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Cols>& mat);
    };

    using Matrix2f = Matrix<float, 2, 2>;
    using Matrix2d = Matrix<double, 2, 2>;
    using Mat2f = Matrix<float, 2, 2>;
    using Mat2 = Matrix<double, 2, 2>;
    using Mat2d = Matrix<double, 2, 2>;

    using Matrix3f = Matrix<float, 3, 3>;
    using Matrix3d = Matrix<double, 3, 3>;
    using Mat3 = Matrix<double, 3, 3>;
    using Mat3f = Matrix<float, 3, 3>;
    using Mat3d = Matrix<double, 3, 3>;

    using Matrix4f = Matrix<float, 4, 4>;
    using Matrix4d = Matrix<double, 4, 4>;
    using Mat4 = Matrix<double, 4, 4>;
    using Mat4f = Matrix<float, 4, 4>;
    using Mat4d = Matrix<double, 4, 4>;
} // namespace Ut

#endif // MATRIX_H