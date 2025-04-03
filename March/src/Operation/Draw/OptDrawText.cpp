#include "OptDrawText.h"

OptDrawText::OptDrawText(MEngine::Scene* scene) : OptBase(scene) {}
OptDrawText::~OptDrawText() {}

// 实现enter()函数
void OptDrawText::enter()
{
    // 这里可以添加进入绘制文本操作时的具体逻辑
    // 例如，初始化文本绘制所需的数据、显示提示信息等
}

// 实现exit()函数
void OptDrawText::exit()
{
    // 这里可以添加退出绘制文本操作时的具体逻辑
    // 例如，清理文本绘制相关的数据、保存状态等
}

void OptDrawText::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 记录文本起始位置
        QPointF pos = event->pos();
        // 可以在这里弹出输入框输入文本
        // 然后调用 m_scene->addText(...)
    }
}

void OptDrawText::mouseReleaseEvent(QMouseEvent* event)
{
    // 处理鼠标释放事件
}

void OptDrawText::mouseMoveEvent(QMouseEvent* event)
{
    // 处理鼠标移动事件
}

void OptDrawText::wheelEvent(QWheelEvent* event)
{
    // 处理鼠标滚轮事件
}

void OptDrawText::keyPressEvent(QKeyEvent* event)
{
    // 处理按键事件
}