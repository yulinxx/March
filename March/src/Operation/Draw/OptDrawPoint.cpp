#include "OptDrawPoint.h"

OptDrawPoint::OptDrawPoint(MEngine::Scene* scene) : OptBase(scene) {}
OptDrawPoint::~OptDrawPoint() {}

// 实现enter()函数
void OptDrawPoint::enter()
{
    // 这里可以添加进入绘制点操作时的具体逻辑
    // 例如，初始化点绘制所需的数据、显示提示信息等
}

// 实现exit()函数
void OptDrawPoint::exit()
{
    // 这里可以添加退出绘制点操作时的具体逻辑
    // 例如，清理点绘制相关的数据、保存状态等
}

void OptDrawPoint::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        //m_scene->addPoint(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawPoint::mouseReleaseEvent(QMouseEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawPoint::mouseMoveEvent(QMouseEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawPoint::wheelEvent(QWheelEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawPoint::keyPressEvent(QKeyEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}