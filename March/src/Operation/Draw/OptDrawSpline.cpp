#include "OptDrawSpline.h"
#include "Entity/CubicBSpline.h"
#include "Command/AddEntityCmd.h"
#include <QPointF>

OptDrawSpline::OptDrawSpline(MEngine::Scene* scene)
    : OptBase(scene), m_splinePreview(std::make_shared<MEngine::CubicBSpline>())
{
    m_drawType = DrawType::Spline;
    m_scene->addPreview(m_splinePreview.get());
}

OptDrawSpline::~OptDrawSpline()
{
    m_scene->removePreview(m_splinePreview.get());
}

void OptDrawSpline::enter()
{
    m_drawType = DrawType::Spline;
    m_isDrawing = true;
    m_isClosed = false;
    m_controlPoints.clear();
    m_splinePreview->clear();
    m_viewWrap->updateRender();
}

void OptDrawSpline::exit()
{
    m_scene->removePreview(m_splinePreview.get());
    m_isDrawing = false;
    m_isClosed = false;
    m_isDragging = false;
    m_selectedPointIndex = -1;
    m_controlPoints.clear();
    m_splinePreview->clear();
    m_viewWrap->updateRender();
}

void OptDrawSpline::mousePressEvent(QMouseEvent* event)
{
    QPointF pos = event->pos();
    Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

    if (event->button() == Qt::LeftButton && m_isDrawing)
    {
        // 检查是否靠近已有控制点，若是则准备拖动
        for (int i = 0; i < m_controlPoints.size(); ++i)
        {
            if ((posW - m_controlPoints[i]).length() < DRAG_THRESHOLD / m_scene->getZoom())
            {
                m_isDragging = true;
                m_selectedPointIndex = i;
                m_currentMousePos = posW;
                return;
            }
        }

        // 未选中控制点，则添加新控制点
        m_controlPoints.push_back(posW);
        m_currentMousePos = posW;
        updatePreview();
        m_viewWrap->updateRender();
    }
    else if (event->button() == Qt::RightButton && m_isDrawing)
    {
        if (m_controlPoints.size() >= 4)
        {
            drawSpline();
        }
        m_isDrawing = false; // 结束当前绘制，但允许重新进入绘制模式
        m_controlPoints.clear();
        m_splinePreview->clear();
        m_viewWrap->updateRender();
    }
    else
    {
        Super::mousePressEvent(event);
    }
}

void OptDrawSpline::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isDragging)
    {
        m_isDragging = false;
        m_selectedPointIndex = -1;
        updatePreview();
        m_viewWrap->updateRender();
    }
    Super::mouseReleaseEvent(event);
}

void OptDrawSpline::mouseMoveEvent(QMouseEvent* event)
{
    QPointF pos = event->pos();
    m_currentMousePos = m_scene->screenToWorld({ pos.x(), pos.y() });

    if (m_isDragging && m_selectedPointIndex >= 0)
    {
        m_controlPoints[m_selectedPointIndex] = m_currentMousePos;
        updatePreview();
        m_viewWrap->updateRender();
    }
    else if (m_isDrawing && !m_controlPoints.empty())
    {
        updatePreview();
        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawSpline::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawSpline::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape && m_isDrawing)
    {
        m_isDrawing = false;
        m_controlPoints.clear();
        m_splinePreview->clear();
        m_viewWrap->updateRender();
    }
    else if (event->key() == Qt::Key_C && m_isDrawing)
    {
        m_isClosed = !m_isClosed;
        updatePreview();
        m_viewWrap->updateRender();
    }
    Super::keyPressEvent(event);
}

void OptDrawSpline::setSplineData(MEngine::CubicBSpline* spline)
{
    // 可选：设置样条属性，例如颜色、层等
    // spline->setColor(Qt::blue);
}

void OptDrawSpline::drawSpline()
{
    if (m_controlPoints.size() < 4)
        return;

    MEngine::CubicBSpline* spline = new MEngine::CubicBSpline();
    spline->setControlPoints(m_controlPoints, m_isClosed);
    spline->setSegmentsPerSpan(32);
    setSplineData(spline);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), spline);
    m_scene->execute(std::move(addCmd));
}

void OptDrawSpline::updatePreview()
{
    if (m_controlPoints.empty())
    {
        m_splinePreview->clear();
        return;
    }

    std::vector<Ut::Vec2d> previewPoints = m_controlPoints;
    if (previewPoints.size() < 4)
    {
        // 控制点少于 4 个时，平滑填充至 4 个点
        size_t n = previewPoints.size();
        Ut::Vec2d lastPoint = n > 0 ? previewPoints.back() : m_currentMousePos;
        for (size_t i = n; i < 4; ++i)
        {
            previewPoints.push_back(lastPoint + (m_currentMousePos - lastPoint) * (i - n + 1) / (4 - n));
        }
    }
    else
    {
        previewPoints.push_back(m_currentMousePos);
    }

    m_splinePreview->setControlPoints(previewPoints, m_isClosed);
    m_splinePreview->setSegmentsPerSpan(32);
}