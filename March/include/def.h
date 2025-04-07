#ifndef DEF_H
#define DEF_H

enum EntityOpt
{
    Move,
    Rotate,
    Scale,
    Mirror,
    Delete,
};

enum class DrawType
{
    Select = 0,
    Point,
    Line,
    Polyline,
    Rectangle,
    Polygon,
    Arc,
    Circle,
    Ellipse,
    Spline,
    Bezier,
    Text,
    Image,
    None
};

#endif // DEF_H