#ifndef INDEX_DEF_H
#define INDEX_DEF_H

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "Entity/Entity.h"
#include "MEngineAPI.h"
#include "Ut/Rect.h"
#include <memory>
#include <vector>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            template <typename T, size_t N>
            struct tag<Ut::Vec<T, N>>
            {
                using type = point_tag;
            };

            template <typename T, size_t N>
            struct coordinate_type<Ut::Vec<T, N>>
            {
                using type = T;
            };

            template <typename T, size_t N>
            struct coordinate_system<Ut::Vec<T, N>>
            {
                using type = cs::cartesian;
            };

            template <typename T, size_t N>
            struct dimension<Ut::Vec<T, N>> : boost::mpl::int_<static_cast<int>(N)>
            {
            };

            template <typename T, size_t N>
            struct access<Ut::Vec<T, N>, 0>
            {
                static T get(const Ut::Vec<T, N>& p)
                {
                    return p[0];
                }
                static void set(Ut::Vec<T, N>& p, T value)
                {
                    p[0] = value;
                }
            };

            template <typename T, size_t N>
            struct access<Ut::Vec<T, N>, 1>
            {
                static T get(const Ut::Vec<T, N>& p)
                {
                    static_assert(N >= 2, "Dimension must be >= 2"); return p[1];
                }
                static void set(Ut::Vec<T, N>& p, T value)
                {
                    static_assert(N >= 2, "Dimension must be >= 2"); p[1] = value;
                }
            };

            template <typename T, size_t N>
            struct access<Ut::Vec<T, N>, 2>
            {
                static T get(const Ut::Vec<T, N>& p)
                {
                    static_assert(N >= 3, "Dimension must be >= 3"); return p[2];
                }
                static void set(Ut::Vec<T, N>& p, T value)
                {
                    static_assert(N >= 3, "Dimension must be >= 3"); p[2] = value;
                }
            };

            template <typename T, int DIM>
            struct tag<Ut::Rect<T, DIM>>
            {
                using type = box_tag;
            };

            template <typename T, int DIM>
            struct point_type<Ut::Rect<T, DIM>>
            {
                using type = Ut::Vec<T, DIM>;
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, min_corner, 0>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    return b.min()[0];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    b.setMin(Ut::Vec<T, DIM>(value, b.min()[1]));
                }
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, min_corner, 1>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); return b.min()[1];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); b.setMin(Ut::Vec<T, DIM>(b.min()[0], value));
                }
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, max_corner, 0>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    return b.max()[0];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    b.setMax(Ut::Vec<T, DIM>(value, b.max()[1]));
                }
            };

            template <typename T, int DIM>
            struct indexed_access<Ut::Rect<T, DIM>, max_corner, 1>
            {
                static T get(const Ut::Rect<T, DIM>& b)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); return b.max()[1];
                }
                static void set(Ut::Rect<T, DIM>& b, T value)
                {
                    static_assert(DIM >= 2, "Dimension must be >= 2"); b.setMax(Ut::Vec<T, DIM>(b.max()[0], value));
                }
            };
        }
    }
} // namespace boost::geometry::traits

#endif // INDEX_DEF_H
