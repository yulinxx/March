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
    View = 0,
    Select = 1,
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