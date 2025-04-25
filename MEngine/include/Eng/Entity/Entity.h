#ifndef ENTITY_H
#define ENTITY_H

#include "MEngineAPI.h"
#include "Ut/tools.h"
#include "Ut/Vec.h"
#include "Ut/Rect.h"
#include "Ut/Matrix.h"

namespace MEngine
{
    class Layer;

    enum class EntType
    {
        POINT,
        LINE,
        ARC,
        CIRCLE,
        LWPOLYLINE,
        SPLINE,
        POLYGON,
        TEXT,
        ELLIPSE,
        RECTANGLE,
        BSPLINE,
        BEZIER,
        IMAGE,
        UNKNOWN
    };

    // 定义标志位的枚举
    enum EntFlag
    {
        Select = 0, // 选择标志位
        Show = 1,   // 显示标志位
        Lock = 2,     // 锁定标志位
        Dirty = 3,    // 脏标记标志位
    };

    class MENGINE_API Entity
    {
    public:
        Entity();
        virtual ~Entity();

    public:
        virtual void clear() = 0; // 清除数据

        virtual double getLength() const = 0; // 获取长度
        virtual Ut::Rect2d& getRect();  // 获取边界矩形
        virtual std::pair<Ut::Vec2*, size_t> getData() const = 0; // 获取顶点数据，用于绘制

        virtual void transform(const Ut::Mat3& matrix) = 0; // 变换;

        virtual Ut::Vec2d getValue(double t); // 获取参数t处的值
        virtual double EvalParam(const Ut::Vec2& p); // 获取点p处的t值

    public:
        void setLength(double dLen);    // 设置长度
        void setRect(Ut::Rect2d& rect); // 设置边界矩形
        void setLayer(Layer* laer);     // 设置图层
        Layer* getLayer();                 // 获取图层
        int getLayerColor();                 // 获取图层颜色
        void getLayerColor(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a);
        // void setColor(Ut::Color& color);     // 设置颜色
        // void setLineWidth(double dWidth);     // 设置线宽
        // void setLineType(int nType);     // 设置线型

        // 获取和设置属性
        EntType getType() const;
        size_t getId() const;
        Ut::Vec2d& getBasePoint() const;
        bool isReversed() const;
        bool isClosed() const;

        void setType(EntType type);
        void setId(size_t id);
        void setBasePoint(const Ut::Vec2d& basePt);
        void setReversed(bool reverse);
        void setClosed(bool closed);
        

        void setFlag(EntFlag flag, bool b = true);
        bool getFlag(EntFlag flag) const;

    private:
        struct Impl;
        Impl* m_impl = nullptr;
    };
}

#endif // ENTITY_H
