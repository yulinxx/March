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
    Super::exit();
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
        m_polygonPreview->m_basePt = posW;
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

        setPolygonData(m_polygonPreview.get());
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

void OptDrawPolygon::setPolygonData(MEngine::Polygon* polygon)
{
    polygon->clear();

    const int nSides = 5;
    const Ut::Vec2d center = m_startPoint;
    // 计算半径和起始角度（根据第二个点确定）
    const double dx = m_endPoint.x() - center.x();
    const double dy = m_endPoint.y() - center.y();
    const double radius = sqrt(dx*dx + dy*dy);
    const double startAngle = atan2(dy, dx);  // 获取第二个点相对中心的极角

    for (int i = 0; i < nSides; ++i)
    {
        // 从起始角度开始均匀分布顶点
        double angle = startAngle + 2 * Ut::PI * i / nSides;
        Ut::Vec2d vertex(
            center.x() + radius * cos(angle),
            center.y() + radius * sin(angle)
        );
        polygon->addVertex(vertex);
    }
    polygon->closePolygon();
}

void OptDrawPolygon::drawPolygon()
{
    m_bFirst = true;
    if ((m_endPoint - m_startPoint).length() < 1e-6)
        return;

    MEngine::Polygon* polygon = new MEngine::Polygon();
    setPolygonData(polygon);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), polygon);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}

