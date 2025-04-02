// Rect.h
#ifndef RECT_H
#define RECT_H

#include "Vec.h"
#include <stdexcept>

#ifdef _WIN32
    #ifdef RECT_EXPORTS
        #define RECT_API __declspec(dllexport)
    #else
        #define RECT_API __declspec(dllimport)
    #endif
#else
    #define RECT_API
#endif

namespace Ut {
    template <typename T>
    class RECT_API Rect {
        static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");

    public:
        // Constructors
        Rect() noexcept : origin(), size() {}
        Rect(const Vec<T, 2>& origin, const Vec<T, 2>& size) : origin(origin), size(size) {}
        Rect(T x, T y, T width, T height) : origin(x, y), size(width, height) {}

        // Basic properties
        Vec<T, 2> origin;  // Bottom-left corner
        Vec<T, 2> size;    // width, height

        // Getters
        [[nodiscard]] T x() const noexcept { return origin.x(); }
        [[nodiscard]] T y() const noexcept { return origin.y(); }
        [[nodiscard]] T width() const noexcept { return size.x(); }
        [[nodiscard]] T height() const noexcept { return size.y(); }
        [[nodiscard]] Vec<T, 2> topRight() const noexcept { return origin + size; }
        [[nodiscard]] Vec<T, 2> center() const noexcept { return origin + size * T(0.5); }
        [[nodiscard]] T left() const noexcept { return origin.x(); }
        [[nodiscard]] T right() const noexcept { return origin.x() + size.x(); }
        [[nodiscard]] T bottom() const noexcept { return origin.y(); }
        [[nodiscard]] T top() const noexcept { return origin.y() + size.y(); }
        [[nodiscard]] T area() const noexcept { return size.x() * size.y(); }

        // Setters
        void setOrigin(T x, T y) noexcept { origin = Vec<T, 2>(x, y); }
        void setSize(T width, T height) noexcept { size = Vec<T, 2>(width, height); }

        // Operations
        [[nodiscard]] bool contains(const Vec<T, 2>& point) const noexcept {
            return point.x() >= left() && point.x() <= right() &&
                   point.y() >= bottom() && point.y() <= top();
        }

        [[nodiscard]] bool intersects(const Rect& other) const noexcept {
            return left() < other.right() && right() > other.left() &&
                   bottom() < other.top() && top() > other.bottom();
        }

        [[nodiscard]] Rect intersection(const Rect& other) const {
            if (!intersects(other))
                return Rect();
            
            T newX = std::max(left(), other.left());
            T newY = std::max(bottom(), other.bottom());
            T newWidth = std::min(right(), other.right()) - newX;
            T newHeight = std::min(top(), other.top()) - newY;
            return Rect(newX, newY, newWidth, newHeight);
        }

        [[nodiscard]] Rect unionWith(const Rect& other) const {
            T newX = std::min(left(), other.left());
            T newY = std::min(bottom(), other.bottom());
            T newWidth = std::max(right(), other.right()) - newX;
            T newHeight = std::max(top(), other.top()) - newY;
            return Rect(newX, newY, newWidth, newHeight);
        }

        // Operators
        Rect& operator+=(const Vec<T, 2>& offset) {
            origin += offset;
            return *this;
        }

        Rect& operator-=(const Vec<T, 2>& offset) {
            origin -= offset;
            return *this;
        }

        Rect operator+(const Vec<T, 2>& offset) const {
            return Rect(origin + offset, size);
        }

        Rect operator-(const Vec<T, 2>& offset) const {
            return Rect(origin - offset, size);
        }

        bool operator==(const Rect& other) const {
            return origin == other.origin && size == other.size;
        }

        bool operator!=(const Rect& other) const {
            return !(*this == other);
        }

        friend std::ostream& operator<<(std::ostream& os, const Rect& rect) {
            os << "Rect(origin: " << rect.origin << ", size: " << rect.size << ")";
            return os;
        }
    };

    using Rectf = Rect<float>;
    using Rectd = Rect<double>;
    using Recti = Rect<int>;
}

#endif // RECT_H

// Rect_test.cpp
#include <gtest/gtest.h>
#include "Rect.h"

TEST(RectTest, Construction) {
    Ut::Rectf rect(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(rect.x(), 1.0f);
    EXPECT_FLOAT_EQ(rect.y(), 2.0f);
    EXPECT_FLOAT_EQ(rect.width(), 3.0f);
    EXPECT_FLOAT_EQ(rect.height(), 4.0f);
}

TEST(RectTest, Properties) {
    Ut::Rectf rect(0.0f, 0.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(rect.left(), 0.0f);
    EXPECT_FLOAT_EQ(rect.right(), 2.0f);
    EXPECT_FLOAT_EQ(rect.bottom(), 0.0f);
    EXPECT_FLOAT_EQ(rect.top(), 3.0f);
    EXPECT_FLOAT_EQ(rect.area(), 6.0f);
    
    auto center = rect.center();
    EXPECT_FLOAT_EQ(center.x(), 1.0f);
    EXPECT_FLOAT_EQ(center.y(), 1.5f);
}

TEST(RectTest, Contains) {
    Ut::Rectf rect(0.0f, 0.0f, 2.0f, 2.0f);
    EXPECT_TRUE(rect.contains(Ut::Vec2f(1.0f, 1.0f)));
    EXPECT_FALSE(rect.contains(Ut::Vec2f(3.0f, 3.0f)));
    EXPECT_TRUE(rect.contains(Ut::Vec2f(0.0f, 0.0f)));
    EXPECT_FALSE(rect.contains(Ut::Vec2f(-1.0f, -1.0f)));
}

TEST(RectTest, Intersects) {
    Ut::Rectf rect1(0.0f, 0.0f, 2.0f, 2.0f);
    Ut::Rectf rect2(1.0f, 1.0f, 2.0f, 2.0f);
    Ut::Rectf rect3(3.0f, 3.0f, 2.0f, 2.0f);
    
    EXPECT_TRUE(rect1.intersects(rect2));
    EXPECT_FALSE(rect1.intersects(rect3));
}

TEST(RectTest, Intersection) {
    Ut::Rectf rect1(0.0f, 0.0f, 2.0f, 2.0f);
    Ut::Rectf rect2(1.0f, 1.0f, 2.0f, 2.0f);
    
    auto result = rect1.intersection(rect2);
    EXPECT_FLOAT_EQ(result.x(), 1.0f);
    EXPECT_FLOAT_EQ(result.y(), 1.0f);
    EXPECT_FLOAT_EQ(result.width(), 1.0f);
    EXPECT_FLOAT_EQ(result.height(), 1.0f);
}

TEST(RectTest, Union) {
    Ut::Rectf rect1(0.0f, 0.0f, 2.0f, 2.0f);
    Ut::Rectf rect2(1.0f, 1.0f, 2.0f, 2.0f);
    
    auto result = rect1.unionWith(rect2);
    EXPECT_FLOAT_EQ(result.x(), 0.0f);
    EXPECT_FLOAT_EQ(result.y(), 0.0f);
    EXPECT_FLOAT_EQ(result.width(), 3.0f);
    EXPECT_FLOAT_EQ(result.height(), 3.0f);
}

TEST(RectTest, Operators) {
    Ut::Rectf rect(0.0f, 0.0f, 2.0f, 2.0f);
    Ut::Vec2f offset(1.0f, 1.0f);
    
    auto moved = rect + offset;
    EXPECT_FLOAT_EQ(moved.x(), 1.0f);
    EXPECT_FLOAT_EQ(moved.y(), 1.0f);
    EXPECT_FLOAT_EQ(moved.width(), 2.0f);
    EXPECT_FLOAT_EQ(moved.height(), 2.0f);
    
    EXPECT_TRUE(rect == Ut::Rectf(0.0f, 0.0f, 2.0f, 2.0f));
    EXPECT_FALSE(rect != Ut::Rectf(0.0f, 0.0f, 2.0f, 2.0f));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

