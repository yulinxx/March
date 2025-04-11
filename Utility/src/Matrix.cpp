#include "Matrix.h"
#include <cmath>
#include <iomanip>

namespace Ut
{
    // Default constructor - initializes to identity matrix
    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols>::Matrix() noexcept
    {
        data.fill(T(0));
        for (size_t i = 0; i < std::min(Rows, Cols); ++i)
        {
            at(i, i) = T(1);
        }
    }

    // Fill constructor
    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols>::Matrix(T value) noexcept
    {
        data.fill(value);
    }

    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols>::Matrix(std::initializer_list<T> init)
    {
        if (init.size() == Rows * Cols)
        {
            std::copy(init.begin(), init.end(), data.begin());
        }
        else
        {
            throw std::invalid_argument("Initializer list size must match matrix dimensions");
        }
    }

    // Element access
    template <typename T, size_t Rows, size_t Cols>
    T& Matrix<T, Rows, Cols>::at(size_t row, size_t col)
    {
        if (row >= Rows || col >= Cols) throw std::out_of_range("Matrix index out of range");
        return data[row * Cols + col];
    }

    template <typename T, size_t Rows, size_t Cols>
    const T& Matrix<T, Rows, Cols>::at(size_t row, size_t col) const
    {
        if (row >= Rows || col >= Cols) throw std::out_of_range("Matrix index out of range");
        return data[row * Cols + col];
    }

    template <typename T, size_t Rows, size_t Cols>
    T& Matrix<T, Rows, Cols>::operator()(size_t row, size_t col)
    {
        return at(row, col);
    }

    template <typename T, size_t Rows, size_t Cols>
    const T& Matrix<T, Rows, Cols>::operator()(size_t row, size_t col) const
    {
        return at(row, col);
    }

    // Matrix operations
    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator+(const Matrix& other) const
    {
        Matrix result;
        for (size_t i = 0; i < Rows * Cols; ++i)
        {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator-(const Matrix& other) const
    {
        Matrix result;
        for (size_t i = 0; i < Rows * Cols; ++i)
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::operator*(T scalar) const
    {
        Matrix result;
        for (size_t i = 0; i < Rows * Cols; ++i)
        {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator*=(const Matrix& other)
    {
        *this = *this * other;
        return *this;
    }

    // 初始化列表构造函数
    // template <typename T, size_t Rows, size_t Cols>
    // Matrix<T, Rows, Cols>::Matrix(std::initializer_list<T> init) {
    //     if (init.size() == Rows * Cols) {
    //         std::copy(init.begin(), init.end(), data.begin());
    //     } else {
    //         throw std::invalid_argument("Initializer list size must match matrix dimensions");
    //     }
    // }

    // 初始化列表赋值运算符
    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols>& Matrix<T, Rows, Cols>::operator=(std::initializer_list<T> init)
    {
        if (init.size() == Rows * Cols)
        {
            std::copy(init.begin(), init.end(), data.begin());
        }
        else
        {
            throw std::invalid_argument("Initializer list size must match matrix dimensions");
        }
        return *this;
    }

    template <typename T, size_t Rows, size_t Cols>
    template <size_t OtherCols>
    Matrix<T, Rows, OtherCols> Matrix<T, Rows, Cols>::operator*(const Matrix<T, Cols, OtherCols>& other) const
    {
        Matrix<T, Rows, OtherCols> result;
        for (size_t i = 0; i < Rows; ++i)
        {
            for (size_t j = 0; j < OtherCols; ++j)
            {
                T sum = T(0);
                for (size_t k = 0; k < Cols; ++k)
                {
                    sum += at(i, k) * other.at(k, j);
                }
                result.at(i, j) = sum;
            }
        }
        return result;
    }

    template <typename T, size_t Rows, size_t Cols>
    Vec<T, Rows> Matrix<T, Rows, Cols>::operator*(const Vec<T, Cols>& vec) const
    {
        Vec<T, Rows> result;
        for (size_t i = 0; i < Rows; ++i)
        {
            T sum = T(0);
            for (size_t j = 0; j < Cols; ++j)
            {
                sum += at(i, j) * vec[j];
            }
            result[i] = sum;
        }
        return result;
    }

    // Transformation methods
    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::identity() requires (Rows == Cols)
    {
        data.fill(T(0));
        for (size_t i = 0; i < Rows; ++i)
        {
            at(i, i) = T(1);
        }
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::translation(T x, T y) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> transMat;
        transMat.identity();
        if constexpr (Rows == 4 && Cols == 4)
        {
            transMat.at(0, 3) = x;
            transMat.at(1, 3) = y;
        }
        else if constexpr (Rows == 3 && Cols == 3)
        {
            transMat.at(0, 2) = x;
            transMat.at(1, 2) = y;
        }
        *this *= transMat;
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::translation(const Vec<T, 2>& v) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        translation(v.x(), v.y());
    }

    template <typename T, size_t Rows, size_t Cols>
    Vec<T, 2> Matrix<T, Rows, Cols>::transformPoint(const Vec<T, 2>& point) const requires (Rows == 3 && Cols == 3)
    {
        Vec<T, 3> pt3d(point.x(), point.y(), 1.0);
        auto result = (*this) * pt3d;
        return {result.x()/result.z(), result.y()/result.z()};
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::rotation(T angle) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> rotMat;
        rotMat.identity();
        T c = std::cos(angle);
        T s = std::sin(angle);
        rotMat.at(0, 0) = c;
        rotMat.at(0, 1) = -s;
        rotMat.at(1, 0) = s;
        rotMat.at(1, 1) = c;
        *this *= rotMat;
    }
   
    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::rotation(T angle, T centerX, T centerY) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> trans1, rotMat, trans2;
        trans1.identity();
        rotMat.identity();
        trans2.identity();

        trans1.translation(-centerX, -centerY);
        rotMat.rotation(angle);
        trans2.translation(centerX, centerY);

        *this *= (trans2 * rotMat * trans1);
    }

    template <typename T, size_t Rows, size_t Cols>
    void rotation(T angle, const Vec<T, 2>& pt) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> trans1, rotMat, trans2;
        trans1.identity();
        rotMat.identity();
        trans2.identity();

        trans1.translation(-pt.x(), -pt.y());
        rotMat.rotation(angle);
        trans2.translation(pt.x(), pt.y());

        *this *= (trans2 * rotMat * trans1);
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::scale(T sx, T sy) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> scaleMat;
        scaleMat.identity();
        scaleMat.at(0, 0) = sx;
        scaleMat.at(1, 1) = sy;
        *this *= scaleMat;
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::scale(const Vec<T, 2>& s) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        scale(s.x(), s.y());
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::scale(T sx, T sy, T centerX, T centerY) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> trans1, scaleMat, trans2;
        trans1.identity();
        scaleMat.identity();
        trans2.identity();

        trans1.translation(-centerX, -centerY);
        scaleMat.scale(sx, sy);
        trans2.translation(centerX, centerY);

        *this *= (trans2 * scaleMat * trans1);
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::scale(const Vec<T, 2>& s, const Vec<T, 2>& center) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        scale(s.x(), s.y(), center.x(), center.y());
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::scale(T s) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        scale(s, s);
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::scale(T s, T centerX, T centerY) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        scale(s, s, centerX, centerY);
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::mirrorX() requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> mirrorMat;
        mirrorMat.identity();
        mirrorMat.at(0, 0) = -1;
        *this *= mirrorMat;
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::mirrorY() requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> mirrorMat;
        mirrorMat.identity();
        mirrorMat.at(1, 1) = -1;
        *this *= mirrorMat;
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::mirrorXY() requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> mirrorMat;
        mirrorMat.identity();
        mirrorMat.at(0, 0) = -1;
        mirrorMat.at(1, 1) = -1;
        *this *= mirrorMat;
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::translateAndScale(T tx, T ty, T sx, T sy) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        Matrix<T, Rows, Cols> transMat, scaleMat;
        transMat.identity();
        scaleMat.identity();

        transMat.translation(tx, ty);
        scaleMat.scale(sx, sy);
        *this *= (transMat * scaleMat);
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::translateAndScale(const Vec<T, 2>& translation, const Vec<T, 2>& scale) requires (Rows == 4 && Cols == 4 || Rows == 3 && Cols == 3)
    {
        translateAndScale(translation.x(), translation.y(), scale.x(), scale.y());
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::ortho2D(T left, T right, T bottom, T top) requires (Rows == 3 && Cols == 3)
    {
        if (right == left || top == bottom)
            throw std::runtime_error("Invalid orthographic projection parameters");

        Matrix<T, Rows, Cols> orthoMat;
        orthoMat.identity();
        orthoMat.at(0, 0) = T(2) / (right - left);
        orthoMat.at(1, 1) = T(2) / (top - bottom);
        orthoMat.at(0, 2) = -(right + left) / (right - left);
        orthoMat.at(1, 2) = -(top + bottom) / (top - bottom);
        //*this *= orthoMat;
        *this = orthoMat;
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::ortho(T left, T right, T bottom, T top, T near, T far) requires (Rows == 4 && Cols == 4)
    {
        if (right == left || top == bottom || far == near)
            throw std::runtime_error("Invalid orthographic projection parameters");

        Matrix<T, Rows, Cols> orthoMat;
        orthoMat.identity();
        orthoMat.at(0, 0) = T(2) / (right - left);
        orthoMat.at(1, 1) = T(2) / (top - bottom);
        orthoMat.at(2, 2) = T(-2) / (far - near);
        orthoMat.at(0, 3) = -(right + left) / (right - left);
        orthoMat.at(1, 3) = -(top + bottom) / (top - bottom);
        orthoMat.at(2, 3) = -(far + near) / (far - near);
        *this *= orthoMat;
    }

    template <typename T, size_t Rows, size_t Cols>
    void Matrix<T, Rows, Cols>::ortho(T left, T right, T bottom, T top) requires (Rows == 4 && Cols == 4)
    {
        ortho(left, right, bottom, top, T(-1), T(1));
    }

    // Matrix utilities
    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Cols, Rows> Matrix<T, Rows, Cols>::transpose() const
    {
        Matrix<T, Cols, Rows> result;
        for (size_t i = 0; i < Rows; ++i)
        {
            for (size_t j = 0; j < Cols; ++j)
            {
                result.at(j, i) = at(i, j);
            }
        }
        return result;
    }

    template <typename T, size_t Rows, size_t Cols>
    T Matrix<T, Rows, Cols>::determinant() const requires (Rows == Cols)
    {
        if constexpr (Rows == 2)
        {
            return at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
        }
        else if constexpr (Rows == 3)
        {
            return at(0, 0) * (at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1))
                - at(0, 1) * (at(1, 0) * at(2, 2) - at(1, 2) * at(2, 0))
                + at(0, 2) * (at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0));
        }
        else if constexpr (Rows == 4)
        {
            throw std::runtime_error("4x4 determinant not implemented");
        }
        return T(0);
    }

    template <typename T, size_t Rows, size_t Cols>
    Matrix<T, Rows, Cols> Matrix<T, Rows, Cols>::inverse() const requires (Rows == Cols)
    {
        if constexpr (Rows == 2)
        {
            T det = determinant();
            if (det == T(0)) throw std::runtime_error("Matrix is not invertible");
            Matrix result;
            result.at(0, 0) = at(1, 1) / det;
            result.at(0, 1) = -at(0, 1) / det;
            result.at(1, 0) = -at(1, 0) / det;
            result.at(1, 1) = at(0, 0) / det;
            return result;
        }
        else if constexpr (Rows == 3)
        {
            T det = determinant();
            if (det == T(0)) throw std::runtime_error("Matrix is not invertible");
            Matrix result;
            result.at(0, 0) = (at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1)) / det;
            result.at(0, 1) = -(at(0, 1) * at(2, 2) - at(0, 2) * at(2, 1)) / det;
            result.at(0, 2) = (at(0, 1) * at(1, 2) - at(0, 2) * at(1, 1)) / det;
            result.at(1, 0) = -(at(1, 0) * at(2, 2) - at(1, 2) * at(2, 0)) / det;
            result.at(1, 1) = (at(0, 0) * at(2, 2) - at(0, 2) * at(2, 0)) / det;
            result.at(1, 2) = -(at(0, 0) * at(1, 2) - at(0, 2) * at(1, 0)) / det;
            result.at(2, 0) = (at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0)) / det;
            result.at(2, 1) = -(at(0, 0) * at(2, 1) - at(0, 1) * at(2, 0)) / det;
            result.at(2, 2) = (at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0)) / det;
            return result;
        }
        else if constexpr (Rows == 4)
        {
            // 这里可以使用更复杂的算法，例如高斯 - 约旦消元法
            // 以下是一个简单的实现示例
            T det = determinant();
            if (det == T(0)) throw std::runtime_error("Matrix is not invertible");
            Matrix result;
            // 这里需要实现 4x4 矩阵的求逆算法
            throw std::runtime_error("4x4 inverse implementation is not fully completed");
        }
        else
        {
            throw std::runtime_error("Inverse not implemented for this matrix size");
        }
    }

    // Stream output
    template <typename T, size_t Rows, size_t Cols>
    std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Cols>& mat)
    {
        os << "[\n";
        for (size_t i = 0; i < Rows; ++i)
        {
            os << "  [";
            for (size_t j = 0; j < Cols; ++j)
            {
                os << std::setw(8) << std::fixed << std::setprecision(2) << mat(i, j);
                if (j < Cols - 1) os << ",";
            }
            os << "]";
            if (i < Rows - 1) os << "\n";
        }
        os << "\n]";
        return os;
    }

    // Template instantiations
    template class UTILITY_API Matrix<float, 2, 2>;
    template class UTILITY_API Matrix<double, 2, 2>;
    template class UTILITY_API Matrix<float, 3, 3>;
    template class UTILITY_API Matrix<double, 3, 3>;
    template class UTILITY_API Matrix<float, 4, 4>;
    template class UTILITY_API Matrix<double, 4, 4>;

    template std::ostream& operator<<(std::ostream&, const Matrix<double, 2, 2>&);
    template std::ostream& operator<<(std::ostream&, const Matrix<double, 3, 3>&);
    template std::ostream& operator<<(std::ostream&, const Matrix<double, 4, 4>&);
    template std::ostream& operator<<(std::ostream&, const Matrix<double, 3, 3>&);
    template UTILITY_API Matrix<double, 2, 2> Matrix<double, 2, 2>::operator*<2>(const Matrix<double, 2, 2>&) const;

    template UTILITY_API double& Matrix<double, 3, 3>::operator()(size_t, size_t);
    template UTILITY_API const double& Matrix<double, 3, 3>::operator()(size_t, size_t) const;
    template UTILITY_API Matrix<double, 3, 3> Matrix<double, 3, 3>::operator*<3>(const Matrix<double, 3, 3>&) const;

    template UTILITY_API Matrix<float, 3, 3>& Matrix<float, 3, 3>::operator*=(const Matrix<float, 3, 3>&);
    template UTILITY_API Matrix<float, 3, 3> Matrix<float, 3, 3>::operator*<3>(const Matrix<float, 3, 3>&) const;
    template UTILITY_API Matrix<double, 3, 3>& Matrix<double, 3, 3>::operator*=(const Matrix<double, 3, 3>&);

    template UTILITY_API Matrix<float, 4, 4>& Matrix<float, 4, 4>::operator*=(const Matrix<float, 4, 4>&);
    template UTILITY_API Matrix<double, 4, 4>& Matrix<double, 4, 4>::operator*=(const Matrix<double, 4, 4>&);
} // namespace Ut