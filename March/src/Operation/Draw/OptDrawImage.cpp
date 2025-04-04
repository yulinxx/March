#include "OptDrawImage.h"

OptDrawImage::OptDrawImage(MEngine::Scene* scene) : OptBase(scene)
{
    m_drawType = DrawType::Image;
}

void OptDrawImage::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 记录图像起始位置
        QPointF pos = event->pos();
    }
}

void OptDrawImage::mouseReleaseEvent(QMouseEvent* event)
{
}

void OptDrawImage::mouseMoveEvent(QMouseEvent* event)
{
}

void OptDrawImage::wheelEvent(QWheelEvent* event)
{
}

void OptDrawImage::keyPressEvent(QKeyEvent* event)
{
}