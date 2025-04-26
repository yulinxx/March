#include "OptDrawSpline.h"
#include "Entity/CubicBSpline.h"
#include <QPointF>

OptDrawSpline::OptDrawSpline(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Spline;
    m_splinePreview = std::make_shared<MEngine::CubicBSpline>();
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
    //m_viewWrap->updateRender();
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
        m_isDrawing = false;
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
    Super::mouseReleaseEvent(event);
}

void OptDrawSpline::mouseMoveEvent(QMouseEvent* event)
{
    QPointF pos = event->pos();
    m_currentMousePos = m_scene->screenToWorld({ pos.x(), pos.y() });

    if (m_isDrawing && !m_controlPoints.empty())
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

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, spline);
    m_scene->execute(std::move(addCmd));
}

void OptDrawSpline::updatePreview()
{
    if (m_controlPoints.empty())
    {
        m_splinePreview->clear();
        return;
    }

    m_splinePreview->setControlPoints(m_controlPoints, m_isClosed);
    m_splinePreview->setSegmentsPerSpan(32);
}