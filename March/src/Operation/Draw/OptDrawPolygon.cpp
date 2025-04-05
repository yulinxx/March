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
        m_bFirst = false;  // 进入绘制状态
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
    if (!m_bFirst)  // 在绘制状态下
    {
        QPointF pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });
        
        // 实时更新预览图形
        setPolygonData(m_polygonPreview.get());
        m_viewWrap->updateRender();

    }

    Super::mouseMoveEvent(event);
}

void OptDrawPolygon::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 计算两点距离
        double distance = (m_endPoint - m_startPoint).length();
        
        if (distance > 1e-6) {  // 有效距离时创建多边形
            drawPolygon();
        }
        
        m_bFirst = true;  // 重置绘制状态
        m_polygonPreview->clear();  // 清除预览
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
    const double radius = (m_endPoint - center).length();

    for (int i = 0; i < nSides; ++i)
    {
        double angle = 2 * Ut::PI * i / nSides;
        Ut::Vec2d vertex(
            center.x() + radius * cos(angle),
            center.y() + radius * sin(angle)
        );
        polygon->addVertex(vertex);
    }

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

