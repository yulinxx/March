#ifndef RECT_H
#define RECT_H

#include "Vec.h"
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
            for (int i = 0; i < DIM; ++i) {
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
            for (int i = 0; i < DIM; ++i) {
                minPt[i] = std::min(min[i], maxPt[i]);
                maxPt[i] = std::max(min[i], maxPt[i]);
            }
        }

        void setMax(const Vec<T, DIM>& max)
        {
            for (int i = 0; i < DIM; ++i) {
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

    private:
        Vec<T, DIM> minPt;
        Vec<T, DIM> maxPt;
    };

    // class UTILITY_API AxisAlignedBoundingBox
    // {
    // public:
    //     AxisAlignedBoundingBox();
    //     AxisAlignedBoundingBox(const Vec2d& min, const Vec2d& max);

    //     void setBounds(const Vec2d& min, const Vec2d& max);
    //     Vec2d getCenter() const;
    //     Vec2d getExtent() const;
    //     Vec2d getMinPt() const
    //     {
    //         return minPt;
    //     }
    //     Vec2d getMaxPt() const
    //     {
    //         return maxPt;
    //     }
    //     Vec2d getSize() const;
    //     double getWidth() const;
    //     double getHeight() const;

    //     void expand(double delta);
    //     void expand(const Vec2d& delta);
    //     void expand(const AxisAlignedBoundingBox& aabb);

    //     bool contains(const Vec2d& point) const;

    // private:
    //     Vec2d minPt;
    //     Vec2d maxPt;
    // };

    // class UTILITY_API TightBoundingBox
    // {
    // public:
    //     TightBoundingBox();

    //     void computeFromPoints(const std::vector<Vec2d>& points);
    //     Vec2d getCenter() const;
    //     Vec2d getExtent() const;
    //     bool contains(const Vec2d& point) const;

    // public:
    //     Vec2d minPt;
    //     Vec2d maxPt;
    // };

    using Box = Ut::Rect<double, 2>;
    using Rect2d = Rect<double, 2>;
    using Rect2f = Rect<float, 2>;
    using Rect3d = Rect<double, 3>;
    using Rect3f = Rect<float, 3>;

    //using AABB = AxisAlignedBoundingBox;
    //using TBB = TightBoundingBox;
} // namespace Ut

#endif // RECT_H