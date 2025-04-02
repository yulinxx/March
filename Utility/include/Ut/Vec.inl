#ifndef VEC_H
#define VEC_H

#include "Vec.h"

namespace Ut
{
    // Constructors
    template <typename T, size_t N>
    Vec<T, N>::Vec() noexcept : data{} {}

    template <typename T, size_t N>
    Vec<T, N>::Vec(T value) noexcept : data{}
    {
        for (size_t i = 0; i < N; ++i) data[i] = value;
    }

    template <typename T, size_t N>
    template <typename... Args>
    requires (sizeof...(Args) == N) Vec<T, N>::Vec(Args... args) noexcept : data{static_cast<T>(args)...} {}

    // Accessors
    template <typename T, size_t N>
    [[nodiscard]] T& Vec<T, N>::x() noexcept requires (N >= 1)
    {
        return data[0];
    }

    template <typename T, size_t N>
    [[nodiscard]] T& Vec<T, N>::y() noexcept requires (N >= 2)
    {
        return data[1];
    }

    template <typename T, size_t N>
    [[nodiscard]] T& Vec<T, N>::z() noexcept requires (N >= 3)
    {
        return data[2];
    }

    template <typename T, size_t N>
    [[nodiscard]] const T& Vec<T, N>::x() const noexcept requires (N >= 1)
    {
        return data[0];
    }

    template <typename T, size_t N>
    [[nodiscard]] const T& Vec<T, N>::y() const noexcept requires (N >= 2)
    {
        return data[1];
    }

    template <typename T, size_t N>
    [[nodiscard]] const T& Vec<T, N>::z() const noexcept requires (N >= 3)
    {
        return data[2];
    }

    // Setters
    template <typename T, size_t N>
    void Vec<T, N>::setX(T value) noexcept requires (N >= 1)
    {
        data[0] = value;
    }

    template <typename T, size_t N>
    void Vec<T, N>::setY(T value) noexcept requires (N >= 2)
    {
        data[1] = value;
    }

    template <typename T, size_t N>
    void Vec<T, N>::setZ(T value) noexcept requires (N >= 3)
    {
        data[2] = value;
    }

    // Operators
    template <typename T, size_t N>
    T& Vec<T, N>::operator[](size_t index) noexcept
    {
        return at(index);
    }

    template <typename T, size_t N>
    const T& Vec<T, N>::operator[](size_t index) const noexcept
    {
        return at(index);
    }

    template <typename T, size_t N>
    Vec<T, N> Vec<T, N>::operator+(const Vec<T, N>& other) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < N; ++i) result[i] = data[i] + other[i];
        return result;
    }

    template <typename T, size_t N>
    Vec<T, N> Vec<T, N>::operator-(const Vec<T, N>& other) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < N; ++i) result[i] = data[i] - other[i];
        return result;
    }

    template <typename T, size_t N>
    Vec<T, N> Vec<T, N>::operator*(T scalar) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < N; ++i) result[i] = data[i] * scalar;
        return result;
    }

    template <typename T, size_t N>
    Vec<T, N> operator*(T scalar, const Vec<T, N>& vec)
    {
        Vec<T, N> result;
        for (size_t i = 0; i < N; ++i) result[i] = scalar * vec[i];
        return result;
    }

    template <typename T, size_t N>
    Vec<T, N> Vec<T, N>::operator/(T scalar) const
    {
        if (scalar == T(0)) throw std::runtime_error("Division by zero in Vec");
        Vec<T, N> result;
        for (size_t i = 0; i < N; ++i) result[i] = data[i] / scalar;
        return result;
    }

    template <typename T, size_t N>
    Vec<T, N>& Vec<T, N>::operator+=(const Vec<T, N>& other)
    {
        for (size_t i = 0; i < N; ++i) data[i] += other[i];
        return *this;
    }

    template <typename T, size_t N>
    Vec<T, N>& Vec<T, N>::operator-=(const Vec<T, N>& other)
    {
        for (size_t i = 0; i < N; ++i) data[i] -= other[i];
        return *this;
    }

    template <typename T, size_t N>
    Vec<T, N>& Vec<T, N>::operator*=(T scalar)
    {
        for (size_t i = 0; i < N; ++i) data[i] *= scalar;
        return *this;
    }

    template <typename T, size_t N>
    Vec<T, N>& Vec<T, N>::operator/=(T scalar)
    {
        if (scalar == T(0)) throw std::runtime_error("Division by zero in Vec");
        for (size_t i = 0; i < N; ++i) data[i] /= scalar;
        return *this;
    }

    template <typename T, size_t N>
    bool Vec<T, N>::operator==(const Vec<T, N>& other) const
    {
        for (size_t i = 0; i < N; ++i) if (data[i] != other[i]) return false;
        return true;
    }

    template <typename T, size_t N>
    bool Vec<T, N>::operator!=(const Vec<T, N>& other) const
    {
        return !(*this == other);
    }

    // Mathematical operations
    template <typename T, size_t N>
    [[nodiscard]] T Vec<T, N>::dot(const Vec<T, N>& other) const noexcept
    {
        T result = T();
        for (size_t i = 0; i < N; ++i) result += data[i] * other[i];
        return result;
    }

    template <typename T, size_t N>
    [[nodiscard]] Vec<T, N> Vec<T, N>::cross(const Vec<T, N>& other) const requires (N == 3)
    {
        return Vec<T, N>(
            data[1] * other[2] - data[2] * other[1],
            data[2] * other[0] - data[0] * other[2],
            data[0] * other[1] - data[1] * other[0]);
    }

    template <typename T, size_t N>
    [[nodiscard]] T Vec<T, N>::lengthSquared() const noexcept
    {
        return dot(*this);
    }

    template <typename T, size_t N>
    [[nodiscard]] T Vec<T, N>::length() const
    {
        return std::sqrt(lengthSquared());
    }

    template <typename T, size_t N>
    [[nodiscard]] Vec<T, N> Vec<T, N>::normalize() const
    {
        T len = length();
        if (len == T(0)) throw std::runtime_error("Cannot normalize a zero vector");
        return *this / len;
    }

    template <typename T, size_t N>
    [[nodiscard]] T Vec<T, N>::angle(const Vec<T, N>& other) const
    {
        T lenProduct = length() * other.length();
        if (lenProduct == T(0)) throw std::runtime_error("Cannot compute angle with zero vector");
        return std::acos(dot(other) / lenProduct);
    }

    template <typename T, size_t N>
    [[nodiscard]] T Vec<T, N>::distance(const Vec<T, N>& other) const
    {
        return (*this - other).length();
    }

    template <typename T, size_t N>
    [[nodiscard]] Vec<T, N> Vec<T, N>::lerp(const Vec<T, N>& a, const Vec<T, N>& b, T t)
    {
        return a + (b - a) * t;
    }

    template <typename T, size_t N>
    [[nodiscard]] Vec<T, N> Vec<T, N>::project(const Vec<T, N>& other) const
    {
        T lenSq = other.dot(other);
        if (lenSq == T(0)) throw std::runtime_error("Cannot project onto zero vector");
        return other * (dot(other) / lenSq);
    }

    template <typename T, size_t N>
    [[nodiscard]] Vec<T, N> Vec<T, N>::reflect(const Vec<T, N>& normal) const
    {
        return *this - T(2) * dot(normal) * normal;
    }

    // Utility
    template <typename T, size_t N>
    [[nodiscard]] bool Vec<T, N>::isZero() const noexcept
    {
        return lengthSquared() < std::numeric_limits<T>::epsilon();
    }

    template <typename T, size_t N>
    std::ostream& operator<<(std::ostream& os, const Vec<T, N>& vec)
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

    // Private methods
    template <typename T, size_t N>
    T& Vec<T, N>::at(size_t index)
    {
        if (index >= N) throw std::out_of_range("Vec index out of range");
        return data[index];
    }

    template <typename T, size_t N>
    const T& Vec<T, N>::at(size_t index) const
    {
        if (index >= N) throw std::out_of_range("Vec index out of range");
        return data[index];
    }
}

#endif // VEC_H