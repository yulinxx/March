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
    Polygon,
    Arc,
    Circle,
    Ellipse,
    Spline,
    Text,
    Image,
    BezierCurve,
    Rectangle,
    None
};

#endif // DEF_H