// #ifndef RECT_H
// #define RECT_H

// #include "Vec.h"
// #include <algorithm>

// // 导出宏，用于DLL导出
// #ifdef DLL_EXPORT
//     #define DLL_API extern "C" __declspec(dllexport)
// #else
//     #define DLL_API extern "C" __declspec(dllimport)
// #endif

// namespace Ut
// {
//     template <typename T>
//     class Rect
//     {
//     public:
//         // Constructors
//         Rect() noexcept : minPoint(T(0), T(0)), maxPoint(T(0), T(0)) {}
//         Rect(const Vec<T, 2>& min, const Vec<T, 2>& max) noexcept : minPoint(min), maxPoint(max) {}
//         Rect(T minX, T minY, T maxX, T maxY) noexcept : minPoint(minX, minY), maxPoint(maxX, maxY) {}

//         // Getters
//         [[nodiscard]] const Vec<T, 2>& min() const noexcept { return minPoint; }
//         [[nodiscard]] const Vec<T, 2>& max() const noexcept { return maxPoint; }
//         [[nodiscard]] T width() const noexcept { return maxPoint.x() - minPoint.x(); }
//         [[nodiscard]] T height() const noexcept { return maxPoint.y() - minPoint.y(); }
//         [[nodiscard]] T area() const noexcept { return width() * height(); }
//         [[nodiscard]] T perimeter() const noexcept { return 2 * (width() + height()); }
//         [[nodiscard]] Vec<T, 2> center() const noexcept { return (minPoint + maxPoint) * T(0.5); }

//         // Check if a point is inside the rectangle
//         [[nodiscard]] bool contains(const Vec<T, 2>& point) const noexcept
//         {
//             return (point.x() >= minPoint.x() && point.x() <= maxPoint.x() &&
//                     point.y() >= minPoint.y() && point.y() <= maxPoint.y());
//         }

//         // Check if another rectangle intersects with this one
//         [[nodiscard]] bool intersects(const Rect& other) const noexcept
//         {
//             return (minPoint.x() < other.maxPoint.x() && maxPoint.x() > other.minPoint.x() &&
//                     minPoint.y() < other.maxPoint.y() && maxPoint.y() > other.minPoint.y());
//         }

//         // Get the intersection area with another rectangle
//         [[nodiscard]] Rect intersection(const Rect& other) const noexcept
//         {
//             Vec<T, 2> newMin(
//                 std::max(minPoint.x(), other.minPoint.x()),
//                 std::max(minPoint.y(), other.minPoint.y())
//             );
//             Vec<T, 2> newMax(
//                 std::min(maxPoint.x(), other.maxPoint.x()),
//                 std::min(maxPoint.y(), other.maxPoint.y())
//             );
//             return Rect(newMin, newMax);
//         }

//         // Merge with another rectangle to form a larger enclosing rectangle
//         [[nodiscard]] Rect merge(const Rect& other) const noexcept
//         {
//             Vec<T, 2> newMin(
//                 std::min(minPoint.x(), other.minPoint.x()),
//                 std::min(minPoint.y(), other.minPoint.y())
//             );
//             Vec<T, 2> newMax(
//                 std::max(maxPoint.x(), other.maxPoint.x()),
//                 std::max(maxPoint.y(), other.maxPoint.y())
//             );
//             return Rect(newMin, newMax);
//         }

//         // Operators
//         bool operator==(const Rect& other) const noexcept
//         {
//             return minPoint == other.minPoint && maxPoint == other.maxPoint;
//         }

//         bool operator!=(const Rect& other) const noexcept
//         {
//             return !(*this == other);
//         }

//         Rect& operator+=(const Vec<T, 2>& offset) noexcept
//         {
//             minPoint += offset;
//             maxPoint += offset;
//             return *this;
//         }

//         Rect& operator-=(const Vec<T, 2>& offset) noexcept
//         {
//             minPoint -= offset;
//             maxPoint -= offset;
//             return *this;
//         }

//         Rect& operator*=(T scalar) noexcept
//         {
//             minPoint *= scalar;
//             maxPoint *= scalar;
//             return *this;
//         }

//         Rect& operator/=(T scalar) noexcept
//         {
//             minPoint /= scalar;
//             maxPoint /= scalar;
//             return *this;
//         }

//         friend Rect operator+(Rect rect, const Vec<T, 2>& offset)
//         {
//             return rect += offset;
//         }

//         friend Rect operator-(Rect rect, const Vec<T, 2>& offset)
//         {
//             return rect -= offset;
//         }

//         friend Rect operator*(Rect rect, T scalar)
//         {
//             return rect *= scalar;
//         }

//         friend Rect operator*(T scalar, Rect rect)
//         {
//             return rect *= scalar;
//         }

//         friend Rect operator/(Rect rect, T scalar)
//         {
//             return rect /= scalar;
//         }

//         friend std::ostream& operator<<(std::ostream& os, const Rect& rect)
//         {
//             os << "Rect[Min: " << rect.minPoint << ", Max: " << rect.maxPoint << "]";
//             return os;
//         }

//     private:
//         Vec<T, 2> minPoint; // Minimum point (left-top)
//         Vec<T, 2> maxPoint; // Maximum point (right-bottom)
//     };

//     // Type aliases for common types
//     using Rect2f = Rect<float>;
//     using Rect2 = Rect<double>;
//     using Rect2d = Rect<double>;
//     using Rect2i = Rect<int>;
// }

// // DLL Export Functions
// DLL_API Ut::Rect2 createRect2(Ut::Vec2 min, Ut::Vec2 max)
// {
//     return Ut::Rect2(min, max);
// }

// DLL_API double rect2Area(const Ut::Rect2& rect)
// {
//     return rect.area();
// }

// DLL_API bool rect2Contains(const Ut::Rect2& rect, const Ut::Vec2& point)
// {
//     return rect.contains(point);
// }

// DLL_API bool rect2Intersects(const Ut::Rect2& a, const Ut::Rect2& b)
// {
//     return a.intersects(b);
// }

// DLL_API Ut::Rect2 rect2Intersection(const Ut::Rect2& a, const Ut::Rect2& b)
// {
//     return a.intersection(b);
// }

// DLL_API Ut::Rect2 rect2Merge(const Ut::Rect2& a, const Ut::Rect2& b)
// {
//     return a.merge(b);
// }

// #endif // RECT_H



// #include <gtest/gtest.h>
// #include "Rect.h"

// TEST(RectTest, Constructor)
// {
//     Ut::Rect2 rect(Ut::Vec2(1.0, 2.0), Ut::Vec2(3.0, 4.0));
//     EXPECT_DOUBLE_EQ(rect.min().x(), 1.0);
//     EXPECT_DOUBLE_EQ(rect.min().y(), 2.0);
//     EXPECT_DOUBLE_EQ(rect.max().x(), 3.0);
//     EXPECT_DOUBLE_EQ(rect.max().y(), 4.0);
// }

// TEST(RectTest, AreaAndPerimeter)
// {
//     Ut::Rect2 rect(Ut::Vec2(1.0, 1.0), Ut::Vec2(3.0, 3.0));
//     EXPECT_DOUBLE_EQ(rect.area(), 4.0);
//     EXPECT_DOUBLE_EQ(rect.perimeter(), 8.0);
// }

// TEST(RectTest, ContainsPoint)
// {
//     Ut::Rect2 rect(Ut::Vec2(1.0, 1.0), Ut::Vec2(3.0, 3.0));
//     EXPECT_TRUE(rect.contains(Ut::Vec2(2.0, 2.0)));
//     EXPECT_FALSE(rect.contains(Ut::Vec2(0.0, 0.0)));
//     EXPECT_TRUE(rect.contains(Ut::Vec2(1.0, 1.0))); // Boundary point
//     EXPECT_TRUE(rect.contains(Ut::Vec2(3.0, 3.0))); // Boundary point
// }

// TEST(RectTest, Intersects)
// {
//     Ut::Rect2 rect1(Ut::Vec2(1.0, 1.0), Ut::Vec2(3.0, 3.0));
//     Ut::Rect2 rect2(Ut::Vec2(2.0, 2.0), Ut::Vec2(4.0, 4.0));
//     Ut::Rect2 rect3(Ut::Vec2(4.0, 4.0), Ut::Vec2(5.0, 5.0));

//     EXPECT_TRUE(rect1.intersects(rect2));
//     EXPECT_FALSE(rect1.intersects(rect3));
// }

// TEST(RectTest, Intersection)
// {
//     Ut::Rect2 rect1(Ut::Vec2(1.0, 1.0), Ut::Vec2(3.0, 3.0));
//     Ut::Rect2 rect2(Ut::Vec2(2.0, 2.0), Ut::Vec2(4.0, 4.0));
//     Ut::Rect2 intersection = rect1.intersection(rect2);

//     EXPECT_DOUBLE_EQ(intersection.min().x(), 2.0);
//     EXPECT_DOUBLE_EQ(intersection.min().y(), 2.0);
//     EXPECT_DOUBLE_EQ(intersection.max().x(), 3.0);
//     EXPECT_DOUBLE_EQ(intersection.max().y(), 3.0);
// }

// TEST(RectTest, Merge)
// {
//     Ut::Rect2 rect1(Ut::Vec2(1.0, 1.0), Ut::Vec2(3.0, 3.0));
//     Ut::Rect2 rect2(Ut::Vec2(2.0, 2.0), Ut::Vec2(4.0, 4.0));
//     Ut::Rect2 merged = rect1.merge(rect2);

//     EXPECT_DOUBLE_EQ(merged.min().x(), 1.0);
//     EXPECT_DOUBLE_EQ(merged.min().y(), 1.0);
//     EXPECT_DOUBLE_EQ(merged.max().x(), 4.0);
//     EXPECT_DOUBLE_EQ(merged.max().y(), 4.0);
// }

// TEST(RectTest, Operators)
// {
//     Ut::Rect2 rect(Ut::Vec2(1.0, 1.0), Ut::Vec2(3.0, 3.0));
//     Ut::Rect2 rect2 = rect + Ut::Vec2(1.0, 1.0);
//     EXPECT_DOUBLE_EQ(rect2.min().x(), 2.0);
//     EXPECT_DOUBLE_EQ(rect2.min().y(), 2.0);
//     EXPECT_DOUBLE_EQ(rect2.max().x(), 4.0);
//     EXPECT_DOUBLE_EQ(rect2.max().y(), 4.0);

//     rect2 = rect * 2.0;
//     EXPECT_DOUBLE_EQ(rect2.min().x(), 2.0);
//     EXPECT_DOUBLE_EQ(rect2.min().y(), 2.0);
//     EXPECT_DOUBLE_EQ(rect2.max().x(), 6.0);
//     EXPECT_DOUBLE_EQ(rect2.max().y(), 6.0);
// }

// int main(int argc, char** argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }