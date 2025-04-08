#include "OptDrawPolygon.h"

#include "Eng/Entity/Polygon.h"
#include "Command/AddEntityCmd.h"

OptDrawPolygon::OptDrawPolygon(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Polygon;

    m_polygonPreview = std::make_unique<MEngine::Polygon>();
    m_scene->addPreview(m_polygonPreview.get());
}

void OptDrawPolygon::enter()
{
    m_bFirst = true;
}

void OptDrawPolygon::exit()
{
    m_scene->removePreview(m_polygonPreview.get());
    m_bFirst = false;
}

void OptDrawPolygon::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        // 记录起始点并开始绘制
        m_startPoint = posW;
        m_polygonPreview->setBasePoint(posW);
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

void OptDrawPolygon::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_bFirst)
    {
        QPointF pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });

        m_polygonPreview->setPts(m_startPoint, m_endPoint);

        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawPolygon::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        double distance = (m_endPoint - m_startPoint).length();

        if (distance > 1e-3)
        {
            drawPolygon();
        }

        m_bFirst = true;
        m_polygonPreview->clear();
        m_viewWrap->updateRender();
    }

    Super::mouseReleaseEvent(event);
}

void OptDrawPolygon::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawPolygon::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_bFirst = true;
    }
    Super::keyPressEvent(event);
}

void OptDrawPolygon::drawPolygon()
{
    m_bFirst = true;
    if ((m_endPoint - m_startPoint).length() < 1e-3)
        return;

    MEngine::Polygon* polygon = new MEngine::Polygon();
    //setPolygonData(polygon);
    polygon->setPts(m_startPoint, m_endPoint);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, polygon);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}