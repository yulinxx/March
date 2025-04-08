#include "OptDrawRectangle.h"
#include "Eng/Entity/Rectangle.h"
#include "Command/AddEntityCmd.h"

OptDrawRectangle::OptDrawRectangle(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Rectangle;

    m_rectPreview = std::make_unique<MEngine::Rectangle>();
    m_scene->addPreview(m_rectPreview.get());
}

void OptDrawRectangle::enter()
{
    m_bFirst = true;
}

void OptDrawRectangle::exit()
{
    m_scene->removePreview(m_rectPreview.get());
    m_bFirst = false;
}

void OptDrawRectangle::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        // 记录起始点并开始绘制
        m_startPoint = posW;
        m_rectPreview->setBasePoint(posW);
        m_bFirst = false;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        Super::mousePressEvent(event);
    }
    else if (event->button() == Qt::RightButton)
    {
        Super::mousePressEvent(event);
    }
}

void OptDrawRectangle::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_bFirst)
    {
        QPointF pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });

        setRectangleData(m_rectPreview.get());
        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawRectangle::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        double distance = (m_endPoint - m_startPoint).length();

        if (distance > 1e-3)
        {
            drawRectange();
        }

        m_bFirst = true;
        m_rectPreview->clear();
        m_viewWrap->updateRender();
    }

    Super::mouseReleaseEvent(event);
}

void OptDrawRectangle::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawRectangle::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_bFirst = true;
    }
    Super::keyPressEvent(event);
}

void OptDrawRectangle::setRectangleData(MEngine::Rectangle* rectangle)
{
    rectangle->clear();
    rectangle->setPts(m_startPoint, m_endPoint);
}

void OptDrawRectangle::drawRectange()
{
    m_bFirst = true;
    if ((m_endPoint - m_startPoint).length() < 1e-3)
        return;

    MEngine::Rectangle* rectangle = new MEngine::Rectangle();
    setRectangleData(rectangle);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, rectangle);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}