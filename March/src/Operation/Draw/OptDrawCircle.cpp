#include "OptDrawCircle.h"

OptDrawCircle::OptDrawCircle(MEngine::Scene* scene) : OptBase(scene) {}
OptDrawCircle::~OptDrawCircle() {}

// 实现enter()函数
void OptDrawCircle::enter()
{
    // 这里可以添加进入绘制圆形操作时的具体逻辑
    // 例如，初始化圆形绘制所需的数据、显示提示信息等
}

// 实现exit()函数
void OptDrawCircle::exit()
{
    // 这里可以添加退出绘制圆形操作时的具体逻辑
    // 例如，清理圆形绘制相关的数据、保存状态等
}

void OptDrawCircle::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        // m_scene->setCenterPoint(Ut::Vec2d(pos.x(), pos.y()));
    }
}

void OptDrawCircle::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // QPointF center = m_scene->getCenterPoint();
        // QPointF edge = event->pos();
        // m_scene->addCircle(Ut::Vec2d(center.x(), center.y()), Ut::Vec2d(edge.x(), edge.y()));
    }
}

void OptDrawCircle::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // QPointF center = m_scene->getCenterPoint();
        // QPointF edge = event->pos();
        // m_scene->updateTempCircle(Ut::Vec2d(center.x(), center.y()), Ut::Vec2d(edge.x(), edge.y()));
    }
}

void OptDrawCircle::wheelEvent(QWheelEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}

void OptDrawCircle::keyPressEvent(QKeyEvent* event)
{
    // 可根据需要添加自定义处理逻辑
}