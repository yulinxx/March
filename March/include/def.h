#ifndef DEF_H
#define DEF_H

enum class EntityOpt
{
    Select,
    Move,
    Rotate,
    Scale,
    Mirror,
    Delete,
    None
};

enum class DrawType
{
    Point,
    Line,
    Polyline,
    Polygon,
    Circle,
    Ellipse,
    Arc,
    Spline,
    Text,
    Image,
    None
};

#endif // DEF_H