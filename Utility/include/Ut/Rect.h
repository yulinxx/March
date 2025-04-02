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
        Rect() : min_(Vec<T, DIM>()), max_(Vec<T, DIM>())
        {
        }
        Rect(const Vec<T, DIM>& min, const Vec<T, DIM>& max)
            : min_(min), max_(max)
        {
        }

        const Vec<T, DIM>& min() const
        {
            return min_;
        }
        const Vec<T, DIM>& max() const
        {
            return max_;
        }
        void setMin(const Vec<T, DIM>& min)
        {
            min_ = min;
        }
        void setMax(const Vec<T, DIM>& max)
        {
            max_ = max;
        }

        bool operator==(const Rect& other) const
        {
            return min_ == other.min_ && max_ == other.max_;
        }
        bool operator!=(const Rect& other) const
        {
            return !(*this == other);
        }

        Rect& merge(const Rect& other)
        {
            for (int i = 0; i < DIM; ++i)
            {
                min_[i] = std::min(min_[i], other.min_[i]);
                max_[i] = std::max(max_[i], other.max_[i]);
            }
            return *this;
        }

        T area() const
        {
            static_assert(DIM == 2, "Area is only defined for 2D rectangles");
            return (max_.x() - min_.x()) * (max_.y() - min_.y());
        }

        T volume() const
        {
            static_assert(DIM == 3, "Volume is only defined for 3D rectangles");
            return (max_.x() - min_.x()) * (max_.y() - min_.y()) * (max_.z() - min_.z());
        }

        bool intersects(const Rect& other) const
        {
            for (int i = 0; i < DIM; ++i)
            {
                if (max_[i] < other.min_[i] || min_[i] > other.max_[i]) return false;
            }
            return true;
        }

        bool contains(const Vec<T, DIM>& point) const
        {
            for (int i = 0; i < DIM; ++i)
            {
                if (point[i] < min_[i] || point[i] > max_[i]) return false;
            }
            return true;
        }

        bool contains(const Rect& other) const
        {
            for (int i = 0; i < DIM; ++i)
            {
                if (other.min_[i] < min_[i] || other.max_[i] > max_[i]) return false;
            }
            return true;
        }

        const Rect<T, DIM>& getRect() const
        {
            return *this;
        }

        Vec<T, DIM> getCenter() const
        {
            return (min_ + max_) * T(0.5);
        }
        Vec<T, DIM> getSize() const
        {
            return max_ - min_;
        }

           // 获取宽度（仅适用于二维和三维矩形）
    T width() const
    {
        static_assert(DIM == 2 || DIM == 3, "Width is only defined for 2D and 3D rectangles");
        return max_.x() - min_.x();
    }

    // 获取高度（仅适用于二维和三维矩形）
    T height() const
    {
        static_assert(DIM == 2 || DIM == 3, "Height is only defined for 2D and 3D rectangles");
        return max_.y() - min_.y();
    }
    private:
        Vec<T, DIM> min_;
        Vec<T, DIM> max_;
    };

    class UTILITY_API AxisAlignedBoundingBox
    {
    public:
        AxisAlignedBoundingBox();
        AxisAlignedBoundingBox(const Vec2d& min, const Vec2d& max);

        void setBounds(const Vec2d& min, const Vec2d& max);
        Vec2d getCenter() const;
        Vec2d getExtent() const;
        Vec2d getMinPt() const
        {
            return minPt;
        }
        Vec2d getMaxPt() const
        {
            return maxPt;
        }
        Vec2d getSize() const;
        double getWidth() const;
        double getHeight() const;

        void expand(double delta);
        void expand(const Vec2d& delta);
        void expand(const AxisAlignedBoundingBox& aabb);

        bool contains(const Vec2d& point) const;

    private:
        Vec2d minPt;
        Vec2d maxPt;
    };

    class UTILITY_API TightBoundingBox
    {
    public:
        TightBoundingBox();

        void computeFromPoints(const std::vector<Vec2d>& points);
        Vec2d getCenter() const;
        Vec2d getExtent() const;
        bool contains(const Vec2d& point) const;

    public:
        Vec2d minPt;
        Vec2d maxPt;
    };

    using Box = Ut::Rect<double, 2>;
    using Rect2d = Rect<double, 2>;
    using Rect2f = Rect<float, 2>;
    using Rect3d = Rect<double, 3>;
    using Rect3f = Rect<float, 3>;

    using AABB = AxisAlignedBoundingBox;
    using TBB = TightBoundingBox;

 
} // namespace Ut

#endif // RECT_H