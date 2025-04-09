#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <limits>
#include <algorithm>

#include "UtilityAPI.h"

namespace Ut
{
    template <typename T, size_t N>
    class Vec
    {
        static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

    public:
        Vec() noexcept : data{}
        {
        }

        explicit Vec(T value) noexcept
        {
            for (size_t i = 0; i < N; ++i) data[i] = value;
        }

        template <typename... Args>
            requires (sizeof...(Args) == N)
        Vec(Args... args) noexcept : data{ static_cast<T>(args)... }
        {
        }

        // 访问器
        T& x() noexcept requires (N >= 1)
        {
            return data[0];
        }
        T& y() noexcept requires (N >= 2)
        {
            return data[1];
        }
        T& z() noexcept requires (N >= 3)
        {
            return data[2];
        }
        const T& x() const noexcept requires (N >= 1)
        {
            return data[0];
        }
        const T& y() const noexcept requires (N >= 2)
        {
            return data[1];
        }
        const T& z() const noexcept requires (N >= 3)
        {
            return data[2];
        }

        // 设置器
        void setX(T value) noexcept requires (N >= 1)
        {
            data[0] = value;
        }
        void setY(T value) noexcept requires (N >= 2)
        {
            data[1] = value;
        }
        void setZ(T value) noexcept requires (N >= 3)
        {
            data[2] = value;
        }

        // 运算符
        T& operator[](size_t index) noexcept
        {
            return at(index);
        }
        const T& operator[](size_t index) const noexcept
        {
            return at(index);
        }

        Vec operator+(const Vec& other) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] + other[i];
            return result;
        }

        Vec operator+(T value) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] + value;
            return result;
        }

        Vec operator-(const Vec& other) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] - other[i];
            return result;
        }

        Vec operator-(T value) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] - value;
            return result;
        }

        Vec operator*(T scalar) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] * scalar;
            return result;
        }

        Vec operator/(T scalar) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] / scalar;
            return result;
        }

        Vec& operator+=(const Vec& other)
        {
            for (size_t i = 0; i < N; ++i) data[i] += other[i];
            return *this;
        }

        Vec& operator+=(T value)
        {
            for (size_t i = 0; i < N; ++i) data[i] += value;
            return *this;
        }

        Vec& operator-=(const Vec& other)
        {
            for (size_t i = 0; i < N; ++i) data[i] -= other[i];
            return *this;
        }

        Vec& operator-=(T value)
        {
            for (size_t i = 0; i < N; ++i) data[i] -= value;
            return *this;
        }

        Vec& operator*=(T scalar)
        {
            for (size_t i = 0; i < N; ++i) data[i] *= scalar;
            return *this;
        }

        Vec& operator/=(T scalar)
        {
            for (size_t i = 0; i < N; ++i) data[i] /= scalar;
            return *this;
        }

        bool operator==(const Vec& other) const
        {
            for (size_t i = 0; i < N; ++i) if (data[i] != other[i]) return false;
            return true;
        }

        bool operator!=(const Vec& other) const
        {
            return !(*this == other);
        }

        Vec operator-() const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = -data[i];
            return result;
        }

        Vec operator*(const Vec& other) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] * other[i];
            return result;
        }

        // 数学运算
        T dot(const Vec& other) const noexcept
        {
            T result = T();
            for (size_t i = 0; i < N; ++i) result += data[i] * other[i];
            return result;
        }

        T cross(const Vec& other) const requires (N == 2)
        {
            return data[0] * other[1] - data[1] * other[0];
        }

        Vec cross(const Vec& other) const requires (N == 3)
        {
            return Vec(
                data[1] * other[2] - data[2] * other[1],
                data[2] * other[0] - data[0] * other[2],
                data[0] * other[1] - data[1] * other[0]);
        }

        T lengthSquared() const noexcept
        {
            T result = T();
            for (size_t i = 0; i < N; ++i) result += data[i] * data[i];
            return result;
        }

        T length() const
        {
            return std::sqrt(lengthSquared());
        }

        Vec normalize() const
        {
            T len = length();
            if (len == T()) return *this;
            return *this / len;
        }

        T angle(const Vec& other) const
        {
            T dotProduct = dot(other);
            T lenProduct = length() * other.length();
            if (lenProduct == T()) return T();
            return std::acos(dotProduct / lenProduct);
        }

        T distance(const Vec& other) const
        {
            return (*this - other).length();
        }

        Vec project(const Vec& other) const
        {
            T otherLenSq = other.lengthSquared();
            if (otherLenSq == T()) return Vec();
            return other * (dot(other) / otherLenSq);
        }

        Vec reflect(const Vec& normal) const
        {
            return *this - normal * (2 * dot(normal));
        }

        // 工具函数
        bool isZero() const noexcept
        {
            for (size_t i = 0; i < N; ++i) if (data[i] != T()) return false;
            return true;
        }

        static Vec lerp(const Vec& a, const Vec& b, T t)
        {
            return a + (b - a) * t;
        }

        // 新增常用函数
        Vec abs() const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = std::abs(data[i]);
            return result;
        }

        T maxComponent() const
        {
            T maxVal = data[0];
            for (size_t i = 1; i < N; ++i) maxVal = std::max(maxVal, data[i]);
            return maxVal;
        }

        T minComponent() const
        {
            T minVal = data[0];
            for (size_t i = 1; i < N; ++i) minVal = std::min(minVal, data[i]);
            return minVal;
        }

        Vec clamp(T minVal, T maxVal) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = std::clamp(data[i], minVal, maxVal);
            return result;
        }

        Vec floor() const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = std::floor(data[i]);
            return result;
        }

        Vec ceil() const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = std::ceil(data[i]);
            return result;
        }

        Vec round() const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = std::round(data[i]);
            return result;
        }

        // 友元函数
        friend Vec operator*(T scalar, const Vec& vec)
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = scalar * vec[i];
            return result;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vec& vec)
        {
            os << "(";
            for (size_t i = 0; i < N; ++i)
            {
                if (i != 0) os << ", ";
                os << vec[i];
            }
            os << ")";
            return os;
        }

    private:
        T data[N];
        T& at(size_t index)
        {
            if (index >= N) throw std::out_of_range("Vec index out of range");
            return data[index];
        }
        const T& at(size_t index) const
        {
            if (index >= N) throw std::out_of_range("Vec index out of range");
            return data[index];
        }
    };

    // 类型别名
    using Vec2f = Vec<float, 2>;
    using Pointf = Vec<float, 2>;
    using Vec2 = Vec<double, 2>;
    using Point = Vec<double, 2>;
    using Vec2d = Vec<double, 2>;
    using Vec2i = Vec<int, 2>;
    using Vec3i = Vec<int, 3>;
    using Vec3f = Vec<float, 3>;
    using Vec3 = Vec<double, 3>;
    using Vec3d = Vec<double, 3>;
    using Vec4f = Vec<float, 4>;
    using Vec4d = Vec<double, 4>;
    using Point3f = Vec<float, 3>;
    using Point3d = Vec<double, 3>;
    using Point3i = Vec<int, 3>;
}

#endif // VEC_H