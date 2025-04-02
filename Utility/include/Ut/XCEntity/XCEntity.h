#ifndef XCENTITY_H
#define XCENTITY_H

// #include "Vec.h"
#include "../Vec.h"
#include <vector>
#include <string>
#include <Eigen/Eigen>

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>

#include "../UtilityAPI.h"

namespace XC
{
    /**
     * @brief 定义实体类型的枚举
     */
    enum ETYPE
    {
        /** 点类型 */
        POINT,
        /** 线类型 */
        LINE,
        /** 圆弧类型 */
        ARC,
        /** 圆类型 */
        CIRCLE,
        /** 轻量级多段线类型 */
        LWPOLYLINE,
        /** 样条曲线类型 */
        SPLINE,
        /** 文本类型 */
        TEXT,
        /** 未知类型 */
        UNKNOWN
    };

    /**
     * @brief 文本样式结构体
     */
    struct XCTextStyle
    {
        /** 文本样式ID */
        int id;
        /** 文本样式名称 */
        std::string Name;
        /** 字体名称 */
        std::string FontName;
        /** 固定高度 */
        int FixedHeight;
        /** 宽度因子 */
        double WidthFactor;
    };

    /**
     * @brief 图层结构体
     */
    struct XCLayer
    {
        /** 图层ID */
        int id;
        /** 图层名称 */
        std::string Name;
        /** 图层标志 */
        int LayerFlag;
        /** 图层颜色 */
        int Color;
    };

    /**
     * @brief 视口结构体
     */
    struct XCViewPort
    {
        /** 视口ID */
        int id;
        /** 视口名称 */
        std::string Name;
        /** 视口中心坐标 */
        Ut::Vec2d ViewCenter;
        /** 视口高度 */
        double ViewHeight;
        /** 视口宽高比 */
        double AspectRatio;
        /** 视口右侧坐标 */
        double Right;
        /** 视口底部坐标 */
        double Bottom;
    };

    /**
     * @brief 切割参数结构体
     */
    struct XCCut
    {
        /** 焦点 */
        int Focus = -1;
        /** 气体压力 */
        int GasPressure = 10;
        /** 激光电流 */
        int LaserCurrent = 100;
        /** 激光模式 */
        int LaserMode = 0;
        /** PWM频率 */
        int PwmFreq = 5000;
        /** 停留时间 */
        int TimeStay = 0;
    };

    /**
     * @brief 穿孔参数结构体
     */
    struct XCPierce
    {
        /** 气体压力 */
        int GasPressure = 0;
        /** 高度 */
        int Height = 15;
        /** 激光电流 */
        int LaserCurrent = 0;
        /** 激光模式 */
        int LaserMode = 0;
        /** PWM频率 */
        int PwmFreq = 0;
        /** PWM占空比 */
        double PwmRatio = .5;
        /** 吹气时间 */
        int TimeBlow = 0;
        /** 焦点时间 */
        int TimeFocus = 0;
        /** 跟随时间 */
        int TimeFollow = 0;
        /** 停留时间 */
        int TimeStay = 0;
    };

    /**
     * @brief 相机参数结构体
     */
    struct CamParam
    {
        /** 激光关闭前延迟时间 */
        int DelayBeforeLaserOff = 0;
        /** 提升高度 */
        int LiftHeight = 30;
        /** 穿孔步数 */
        int PierceStepCount = 1;
        /** 慢速结束速度 */
        int SlowEndSpeed = 3;
        /** 慢速结束长度 */
        int SlowEndLength = 2;
        /** 慢速引入速度 */
        int SlowLeadSpeed = 50;
        /** 慢速引入长度 */
        int SlowLeadLength = 3;
        /** 版本号 */
        int Version = 16102421;
        /** 工作速度 */
        int WorkSpeed = 500;
        /** 穿孔标志 */
        int PierceFlags = 8768;
        /** 切割参数 */
        XCCut cut;
        /** 穿孔参数列表 */
        std::vector<XCPierce> Pierces;
    };

    /**
     * @brief 通道结构体
     */
    struct XCChannel
    {
        /** 通道端口 */
        int ChannelPort;
        /** 参数标志 */
        int ParamFlag;
        /** 是否定义PWM频率函数 */
        bool DefPwmFreqFunc;
        /** 是否定义PWM占空比函数 */
        bool DefPwmRatioFunc;
    };

    /**
     * @brief 实体基类
     */
    struct UTILITY_API XCEntity
    {
        /** 实体类型 */
        ETYPE eType;
        /** 实体ID */
        int id;

    public:

        /** 通道端口 */
        int ChannelPort;
        /** 基点 */
        Ut::Vec2d basePoint;
        /** 是否反转 */
        bool reverse = false;
        /** 是否闭合 */
        bool isClosed = false;

        char* m_LayerName = nullptr;

        /**
         * @brief 根据参数t获取实体上的点
         * @param t 参数值，范围[0, 1]
         * @return 实体上的点坐标
         */
        virtual Ut::Vec2d value(double t)
        {
            return basePoint;
        };
        /**
         * @brief 根据点坐标计算参数t
         * @param p 点坐标
         * @return 参数t的值
         */
        virtual double EvalParam(const Ut::Vec2d& p)
        {
            return 0;
        };
    };

    /**
     * @brief 点实体类
     */
     // 移除原来的结构体定义
     // struct XCPoint : public XCEntity
     // {
     // };

     // struct XCLine : public XCEntity
     // {
     //     ...
     // };

     // struct XCCircle : public XCEntity
     // {
     //     ...
     // };

     // #include "XCPoint.h"
     // #include "XCLine.h"
     // #include "XCCircle.h"
     // #include "XCArc.h"
     // #include "XCPolyLine.h"
     // #include "XCPolyBspline.h"
     // #include "XCText.h"

     // /**
     //  * @brief 圆弧实体类
     //  */
     // struct UTILITY_API XCArc : public XCEntity
     // {
     //     double Radius;
     //     double startAngle;
     //     double endAngle;

     //     virtual Ut::Vec2d value(double t)
     //     {
     //         if (t < 0 || t > 1)
     //             throw "";
     //         if (reverse)
     //             t = 1 - t;
     //         double ang = startAngle + t * (endAngle - startAngle);
     //         return Ut::Vec2d(basePoint.x() + Radius * cos(ang), basePoint.y() + Radius * sin(ang));
     //     };
     //     virtual double EvalParam(const Ut::Vec2d& p)
     //     {
     //         double t;

     //         auto v = (p - basePoint);
     //         double ang = atan2(v.y(), v.x());

     //         if (ang >= startAngle && ang <= endAngle)
     //         {
     //             t = (ang - startAngle) / (endAngle - startAngle);
     //         }

     //         else if ((value(0) - p).squaredNorm() < (value(1) - p).squaredNorm())
     //             t = 0;
     //         else
     //             t = 1.0;
     //         if (reverse)
     //         {
     //             return 1 - t;
     //         }
     //         return t;
     //     }
     // };

     // /**
     //  * @brief 多段线实体类
     //  */
     // struct UTILITY_API XCPolyLine : public XCEntity
     // {
     //     std::vector<std::unique_ptr<XCEntity>> entitylist;

     //     virtual Ut::Vec2d value(double t)
     //     {
     //         if (t < 0 || t > 1)
     //             throw "";
     //         if (reverse)
     //             t = 1 - t;

     //         t *= entitylist.size() - 1;
     //         int n = t;
     //         double tt = t - n;
     //         return entitylist[n]->value(tt);
     //     };

     //     virtual double EvalParam(const Ut::Vec2d& p)
     //     {
     //         double t;
     //         double min_d = 1e+20;

     //         for (auto& item : entitylist)
     //         {
     //             auto t1 = item->EvalParam(p);
     //             auto d = (item->value(t1) - p).norm();
     //             if (d < min_d)
     //             {
     //                 min_d = d;
     //                 t = t1;
     //             }
     //         }

     //         if (reverse)
     //         {
     //             return 1 - t;
     //         }
     //         return t;
     //     }
     // };

     // /**
     //  * @brief 样条曲线实体类
     //  */
     // struct UTILITY_API XCPolyBspline : public XCEntity
     // {
     //     int degree;
     //     std::vector<double> knots;
     //     std::vector<double> weights;
     //     std::vector<Ut::Vec2d> controlPts;
     // };
     // /**
     //  * @brief 文本实体类
     //  */
     // struct UTILITY_API XCText : public XCEntity
     // {
     //     // 这里可以添加 XCText 类的成员变量和成员函数
     //     double BaseHeight;
     //     std::string FontName;
     //     double Height;
     //     std::string text;
     // };

    struct LeadIn
    {
        int LeadType;
        double Length;
        double Angle;
        double ArcRadius;
        double LeadHoleR;
        bool LeadByHole; // 在引入线起点添加小圆
        double pos;
    };

    struct LeadOut
    {
        int LeadType;
        double Length;
        double Angle;
        double ArcRadius;
        double pos;
    };

    struct ToolCompensation
    {
        int Style;
        double Size;
        bool Smooth;
    };

    struct MicroConnect
    {
        double pos;
        bool Flags;
        double Size;
    };

    struct XCEntityInfo
    {
        std::unique_ptr<XCEntity> entity;
        bool consumed = false;
        bool isSubPart = false; // 是否已经识别成零件了

        std::shared_ptr<LeadIn> leadIn;
        std::shared_ptr<LeadOut> leadOut;
        std::shared_ptr<ToolCompensation> toolCompensation;
        std::vector<std::shared_ptr<MicroConnect>> MicroConnects;
        bool isFill = false; // true,阴切，false 阳切
        double startParam = 0;

        Ut::Vec2d start;
        Ut::Vec2d end;
        Eigen::Affine2d transfrom;
        Eigen::Matrix2Xd ps;
        Eigen::Vector4d box;
        XCEntityInfo(std::unique_ptr<XCEntity> _entity) : entity(std::move(_entity))
        {
        }
    };

    struct XCComEntityInfo
    {
        int id;
        std::vector<XCEntityInfo*> entitys;
        Eigen::Matrix2Xd ps;
        Eigen::Vector4d box;
        bool isClosed = false;
        bool isSubPart = false; // 是否已经识别成零件的一部分

        std::vector<std::shared_ptr<XCComEntityInfo>> children;
        std::shared_ptr<XCComEntityInfo> parent = nullptr;
        XCComEntityInfo(std::vector<XCEntityInfo*>& _entitys)
        {
            entitys = _entitys;
        }
        XCComEntityInfo()
        {
        }
    };
}

struct Part
{
    int id = 0;
    std::shared_ptr<XC::XCComEntityInfo> comEntityInfo;
    Eigen::Matrix2Xd contours;
    Eigen::Matrix2Xd simplify;
    Eigen::Matrix2Xd hull;
    Eigen::Vector4d box; // x,y,w,h
    std::vector<std::shared_ptr<Part>> children;
    std::string filename = "";
    int num = 1;
    double area = 0;
    bool isRect = false;
};

// 新增功能示例：为XCEntity类添加一个新的虚函数
// virtual void newFunction() {}
#endif // XCENTITY_H
