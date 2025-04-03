#include "OptDrawImage.h"

OptDrawImage::OptDrawImage(MEngine::Scene* scene) : OptBase(scene)
{
}

void OptDrawImage::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 记录图像起始位置
        QPointF pos = event->pos();
        // 可以在这里选择图像文件，然后调用 m_scene->addImage(...)
    }
}

void OptDrawImage::mouseReleaseEvent(QMouseEvent* event)
{
    // 处理鼠标释放事件
}

void OptDrawImage::mouseMoveEvent(QMouseEvent* event)
{
    // 处理鼠标移动事件
}

void OptDrawImage::wheelEvent(QWheelEvent* event)
{
    // 处理鼠标滚轮事件
}

void OptDrawImage::keyPressEvent(QKeyEvent* event)
{
    // 处理按键事件
}