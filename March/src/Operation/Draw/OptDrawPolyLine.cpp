#include "OptDrawPolyLine.h"
#include "Entity/PolyLine.h"
#include "Render/MarchView.h"

OptDrawPolyLine::OptDrawPolyLine(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Polyline;

    m_polyLinePreview = std::make_shared<MEngine::PolyLine>();
    m_scene->addPreview(m_polyLinePreview.get());
}

OptDrawPolyLine::~OptDrawPolyLine()
{
    m_polyLinePreview.reset();
}

void OptDrawPolyLine::enter()
{
    m_bDrawing = true;
    m_bClosed = false;
    m_points.clear();
}

void OptDrawPolyLine::exit()
{
    m_scene->removePreview(m_polyLinePreview.get());
    m_polyLinePreview->clear();
    m_bDrawing = false;
    m_points.clear();
}

void OptDrawPolyLine::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_bDrawing)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });
        m_points.push_back(posW);

        // 更新预览
        const std::vector<Ut::Vec2> vPts = { posW, posW };
        m_polyLinePreview->setPoints(vPts, m_bClosed);
        //m_viewWrap->updateRender();
    }
    else if (event->button() == Qt::RightButton && m_bDrawing)
    {
        if (m_points.size() >= 2)  // 至少需要 2 个点
        {
            drawPolyLine();
        }

        m_bDrawing = false;
        m_points.clear();
        m_polyLinePreview->clear();
        m_viewWrap->updateRender();
    }
    else
    {
        Super::mousePressEvent(event);
    }
}

void OptDrawPolyLine::mouseReleaseEvent(QMouseEvent* event)
{
    Super::mouseReleaseEvent(event);
}

void OptDrawPolyLine::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bDrawing && !m_points.empty())
    {
        QPointF pos = event->pos();
        m_currentPoint = m_scene->screenToWorld({ pos.x(), pos.y() });

        // 创建临时的顶点列表，包括当前鼠标位置
        std::vector<Ut::Vec2d> previewPoints = m_points;
        previewPoints.push_back(m_currentPoint);
        m_polyLinePreview->setPoints(previewPoints, m_bClosed);
        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawPolyLine::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawPolyLine::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape && m_bDrawing)
    {
        m_bDrawing = false;
        m_points.clear();
        m_polyLinePreview->clear();
        m_viewWrap->updateRender();
    }
    else if (event->key() == Qt::Key_C && m_bDrawing)  // 'C' 键切换闭合状态
    {
        m_bClosed = !m_bClosed;
        m_polyLinePreview->setLayer(m_scene->getLayerManager()->getCurrentLayer());
        m_polyLinePreview->setPoints(m_points, m_bClosed);
        if (!m_points.empty())
        {
            m_polyLinePreview->addPoint(m_currentPoint);  // 更新预览时包括当前点
        }
        m_viewWrap->updateRender();
    }
    Super::keyPressEvent(event);
}

void OptDrawPolyLine::drawPolyLine()
{
    if (m_points.size() < 2)
        return;

    MEngine::PolyLine* polyline = new MEngine::PolyLine();
    polyline->setPoints(m_points, m_bClosed);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, polyline);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}