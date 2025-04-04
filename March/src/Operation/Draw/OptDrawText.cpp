#include "OptDrawText.h"

OptDrawText::OptDrawText(MEngine::Scene* scene) : OptBase(scene)
{
    m_drawType = DrawType::Text;
}

OptDrawText::~OptDrawText()
{
}

void OptDrawText::enter()
{
}

void OptDrawText::exit()
{
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