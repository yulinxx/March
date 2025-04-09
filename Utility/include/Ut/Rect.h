#ifndef RECT_H
#define RECT_H

#include "Vec.h"
#include "tools.h"
#include "UtilityAPI.h"
#include <vector>
#include <algorithm>

namespace Ut
{
    template <typename T, int DIM = 2>
    class Rect
    {
        static_assert(DIM == 2 || DIM == 3, "Rect dimension must be 2 or 3");

    public:
        Rect() : minPt(Vec<T, DIM>()), maxPt(Vec<T, DIM>())
        {
        }

        Rect(const Vec<T, DIM>& min, const Vec<T, DIM>& max)
        {
            for (int i = 0; i < DIM; ++i)
            {
                minPt[i] = std::min(min[i], max[i]);
                maxPt[i] = std::max(min[i], max[i]);
            }
        }

        const Vec<T, DIM>& min() const
        {
            return minPt;
        }
        const Vec<T, DIM>& max() const
        {
            return maxPt;
        }

        void setMin(const Vec<T, DIM>& min)
        {
            minPt = min;

            if (maxPt.length() > Ut::UT_EPSILON)
            {
                for (int i = 0; i < DIM; ++i)
                {
                    minPt[i] = std::min(min[i], maxPt[i]);
                    maxPt[i] = std::max(min[i], maxPt[i]);
                }
            }
        }

        void setMax(const Vec<T, DIM>& max)
        {
            for (int i = 0; i < DIM; ++i)
            {
                minPt[i] = std::min(minPt[i], max[i]);
                maxPt[i] = std::max(minPt[i], max[i]);
            }
        }

        bool operator==(const Rect& other) const
        {
            return minPt == other.minPt && maxPt == other.maxPt;
        }
        bool operator!=(const Rect& other) const
        {
            return !(*this == other);
        }

        Rect& merge(const Rect& other)
        {
            for (int i = 0; i < DIM; ++i)
            {
                minPt[i] = std::min(minPt[i], other.minPt[i]);
                maxPt[i] = std::max(maxPt[i], other.maxPt[i]);
            }
            return *this;
        }

        void expand(const Vec<T, DIM>& point)
        {
            for (int i = 0; i < DIM; ++i)
            {
                minPt[i] = std::min(minPt[i], point[i]);
                maxPt[i] = std::max(maxPt[i], point[i]);
            }
        }

        void expand(double delta)
        {
            minPt -= Vec2d(delta, delta);
            maxPt += Vec2d(delta, delta);
        }



        T area() const
        {
            static_assert(DIM == 2, "Area is only defined for 2D rectangles");
            return (maxPt.x() - minPt.x()) * (maxPt.y() - minPt.y());
        }

        T volume() const
        {
            static_assert(DIM == 3, "Volume is only defined for 3D rectangles");
            return (maxPt.x() - minPt.x()) * (maxPt.y() - minPt.y()) * (maxPt.z() - minPt.z());
        }

        bool intersects(const Rect& other) const
        {
            for (int i = 0; i < DIM; ++i)
            {
                if (maxPt[i] < other.minPt[i] || minPt[i] > other.maxPt[i])
                    return false;
            }
            return true;
        }

        bool contains(const Vec<T, DIM>& point) const
        {
            for (int i = 0; i < DIM; ++i)
            {
                if (point[i] < minPt[i] || point[i] > maxPt[i]) return false;
            }
            return true;
        }

        bool contains(const Rect& other) const
        {
            for (int i = 0; i < DIM; ++i)
            {
                if (other.minPt[i] < minPt[i] || other.maxPt[i] > maxPt[i]) return false;
            }
            return true;
        }

        const Rect<T, DIM>& getRect()
        {
            return *this;
        }

        Vec<T, DIM> getCenter() const
        {
            return (minPt + maxPt) * T(0.5);
        }
        Vec<T, DIM> getSize() const
        {
            return maxPt - minPt;
        }

        // 获取宽度（仅适用于二维和三维矩形）
        T width() const
        {
            static_assert(DIM == 2 || DIM == 3, "Width is only defined for 2D and 3D rectangles");
            return maxPt.x() - minPt.x();
        }

        // 获取高度（仅适用于二维和三维矩形）
        T height() const
        {
            static_assert(DIM == 2 || DIM == 3, "Height is only defined for 2D and 3D rectangles");
            return maxPt.y() - minPt.y();
        }

    public:
        // 获取右上角点（仅适用于二维矩形）
        Vec<T, DIM> getRT() const
        {
            static_assert(DIM == 2, "getRT is only defined for 2D rectangles");
            return Vec<T, DIM>(maxPt.x(), minPt.y());
        }

        // 获取左上角点（仅适用于二维矩形）
        Vec<T, DIM> getLT() const
        {
            static_assert(DIM == 2, "getLT is only defined for 2D rectangles");
            return Vec<T, DIM>(minPt.x(), minPt.y());
        }

        // 获取右下角点（仅适用于二维矩形）
        Vec<T, DIM> getRB() const
        {
            static_assert(DIM == 2, "getRB is only defined for 2D rectangles");
            return Vec<T, DIM>(maxPt.x(), maxPt.y());
        }

        // 获取左下角点（仅适用于二维矩形）
        Vec<T, DIM> getLB() const
        {
            static_assert(DIM == 2, "getLB is only defined for 2D rectangles");
            return Vec<T, DIM>(minPt.x(), maxPt.y());
        }

    private:
        Vec<T, DIM> minPt;
        Vec<T, DIM> maxPt;
    };

    using Box = Ut::Rect<double, 2>;
    using Rect2d = Rect<double, 2>;
    using Rect2f = Rect<float, 2>;
    using Rect3d = Rect<double, 3>;
    using Rect3f = Rect<float, 3>;
} // namespace Ut

#endif // RECT_H