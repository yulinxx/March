#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <limits>

namespace Ut
{
    constexpr double PI = 3.14159265358979323846;
    constexpr double PIx2 = 2.0 * PI;
    constexpr double PIHalf = 0.5 * PI;

    template <typename T, size_t N>
    class Vec
    {
        static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

    public:
        // Constructors
        Vec() noexcept : data{}
        {
        }
        explicit Vec(T value) noexcept
        {
            for (size_t i = 0; i < N; ++i) data[i] = value;
        }
        template <typename... Args>
            requires (sizeof...(Args) == N) Vec(Args... args) noexcept : data{ static_cast<T>(args)... }
        {
        }

        // Accessors
        [[nodiscard]] T& x() noexcept requires (N >= 1)
        {
            return data[0];
        }
        [[nodiscard]] T& y() noexcept requires (N >= 2)
        {
            return data[1];
        }
        [[nodiscard]] T& z() noexcept requires (N >= 3)
        {
            return data[2];
        }
        [[nodiscard]] const T& x() const noexcept requires (N >= 1)
        {
            return data[0];
        }
        [[nodiscard]] const T& y() const noexcept requires (N >= 2)
        {
            return data[1];
        }
        [[nodiscard]] const T& z() const noexcept requires (N >= 3)
        {
            return data[2];
        }

        // Setters
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

        // Operators
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
        Vec operator-(const Vec& other) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] - other[i];
            return result;
        }
        Vec operator*(T scalar) const
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] * scalar;
            return result;
        }
        friend Vec operator*(T scalar, const Vec& vec)
        {
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = scalar * vec[i];
            return result;
        }
        Vec operator/(T scalar) const
        {
            if (scalar == T(0)) throw std::runtime_error("Division by zero in Vec");
            Vec result;
            for (size_t i = 0; i < N; ++i) result[i] = data[i] / scalar;
            return result;
        }
        Vec& operator+=(const Vec& other)
        {
            for (size_t i = 0; i < N; ++i) data[i] += other[i];
            return *this;
        }
        Vec& operator-=(const Vec& other)
        {
            for (size_t i = 0; i < N; ++i) data[i] -= other[i];
            return *this;
        }
        Vec& operator*=(T scalar)
        {
            for (size_t i = 0; i < N; ++i) data[i] *= scalar;
            return *this;
        }
        Vec& operator/=(T scalar)
        {
            if (scalar == T(0)) throw std::runtime_error("Division by zero in Vec");
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

        // Mathematical operations
        [[nodiscard]] T dot(const Vec& other) const noexcept
        {
            T result = T();
            for (size_t i = 0; i < N; ++i) result += data[i] * other[i];
            return result;
        }
        [[nodiscard]] Vec cross(const Vec& other) const requires (N == 3)
        {
            return Vec(
                data[1] * other[2] - data[2] * other[1],
                data[2] * other[0] - data[0] * other[2],
                data[0] * other[1] - data[1] * other[0]);
        }
        [[nodiscard]] T lengthSquared() const noexcept
        {
            return dot(*this);
        }
        [[nodiscard]] T length() const
        {
            return std::sqrt(lengthSquared());
        }
        [[nodiscard]] Vec normalize() const
        {
            T len = length();
            if (len == T(0)) throw std::runtime_error("Cannot normalize a zero vector");
            return *this / len;
        }
        [[nodiscard]] T angle(const Vec& other) const
        {
            T lenProduct = length() * other.length();
            if (lenProduct == T(0)) throw std::runtime_error("Cannot compute angle with zero vector");
            return std::acos(dot(other) / lenProduct);
        }
        [[nodiscard]] T distance(const Vec& other) const
        {
            return (*this - other).length();
        }
        [[nodiscard]] static Vec lerp(const Vec& a, const Vec& b, T t)
        {
            return a + (b - a) * t;
        }
        [[nodiscard]] Vec project(const Vec& other) const
        {
            T lenSq = other.dot(other);
            if (lenSq == T(0)) throw std::runtime_error("Cannot project onto zero vector");
            return other * (dot(other) / lenSq);
        }
        [[nodiscard]] Vec reflect(const Vec& normal) const
        {
            return *this - T(2) * dot(normal) * normal;
        }

        // Utility
        [[nodiscard]] bool isZero() const noexcept
        {
            return lengthSquared() < 1e-6;
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
    using Point3f = Vec<float, 3>;
    using Point3d = Vec<double, 3>;
    using Point3i = Vec<int, 3>;
} // namespace Ut

#endif // VEC_H