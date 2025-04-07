#include "Rect.h"

namespace Ut
{
    // // AxisAlignedBoundingBox
    // AxisAlignedBoundingBox::AxisAlignedBoundingBox() : minPt(Vec2d()), maxPt(Vec2d())
    // {
    // }

    // AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vec2d& min, const Vec2d& max)
    //     : minPt(min), maxPt(max)
    // {
    // }

    // void AxisAlignedBoundingBox::setBounds(const Vec2d& min, const Vec2d& max)
    // {
    //     minPt = min;
    //     maxPt = max;
    // }

    // Vec2d AxisAlignedBoundingBox::getCenter() const
    // {
    //     return (minPt + maxPt) * 0.5;
    // }

    // Vec2d AxisAlignedBoundingBox::getExtent() const
    // {
    //     return (maxPt - minPt) * 0.5;
    // }

    // Vec2d AxisAlignedBoundingBox::getSize() const
    // {
    //     return maxPt - minPt;
    // }

    // double AxisAlignedBoundingBox::getWidth() const
    // {
    //     return maxPt.x() - minPt.x();
    // }

    // double AxisAlignedBoundingBox::getHeight() const
    // {
    //     return maxPt.y() - minPt.y();
    // }

    // void AxisAlignedBoundingBox::expand(double delta)
    // {
    //     minPt -= Vec2d(delta, delta);
    //     maxPt += Vec2d(delta, delta);
    // }

    // void AxisAlignedBoundingBox::expand(const Vec2d& delta)
    // {
    //     minPt -= delta;
    //     maxPt += delta;
    // }

    // void AxisAlignedBoundingBox::expand(const AxisAlignedBoundingBox& aabb)
    // {
    //     minPt = Vec2d(std::min(minPt.x(), aabb.minPt.x()), std::min(minPt.y(), aabb.minPt.y()));
    //     maxPt = Vec2d(std::max(maxPt.x(), aabb.maxPt.x()), std::max(maxPt.y(), aabb.maxPt.y()));
    // }

    // bool AxisAlignedBoundingBox::contains(const Vec2d& point) const
    // {
    //     return point.x() >= minPt.x() && point.x() <= maxPt.x() &&
    //         point.y() >= minPt.y() && point.y() <= maxPt.y();
    // }

    // // TightBoundingBox
    // TightBoundingBox::TightBoundingBox() : minPt(Vec2d()), maxPt(Vec2d())
    // {
    // }

    // void TightBoundingBox::computeFromPoints(const std::vector<Vec2d>& points)
    // {
    //     if (points.empty())
    //     {
    //         minPt = Vec2d();
    //         maxPt = Vec2d();
    //         return;
    //     }
    //     minPt = points[0];
    //     maxPt = points[0];
    //     for (const auto& point : points)
    //     {
    //         minPt.x() = std::min(minPt.x(), point.x());
    //         minPt.y() = std::min(minPt.y(), point.y());
    //         maxPt.x() = std::max(maxPt.x(), point.x());
    //         maxPt.y() = std::max(maxPt.y(), point.y());
    //     }
    // }

    // Vec2d TightBoundingBox::getCenter() const
    // {
    //     return (minPt + maxPt) * 0.5;
    // }

    // Vec2d TightBoundingBox::getExtent() const
    // {
    //     return (maxPt - minPt) * 0.5;
    // }

    // bool TightBoundingBox::contains(const Vec2d& point) const
    // {
    //     return point.x() >= minPt.x() && point.x() <= maxPt.x() &&
    //         point.y() >= minPt.y() && point.y() <= maxPt.y();
    // }

} // namespace Ut