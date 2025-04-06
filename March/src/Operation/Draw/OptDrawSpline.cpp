#include "OptDrawSpline.h"
#include "Entity/CubicBSpline.h"
#include "Command/AddEntityCmd.h"

OptDrawSpline::OptDrawSpline(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Spline;

    m_splinePreview = std::make_shared<MEngine::CubicBSpline>();
    m_scene->addPreview(m_splinePreview.get());
}

OptDrawSpline::~OptDrawSpline()
{
}

void OptDrawSpline::enter()
{
    m_drawType = DrawType::Spline;
    m_bDrawing = true;
    m_bClosed = false;
    m_controlPoints.clear();
}

void OptDrawSpline::exit()
{
    m_scene->removePreview(m_splinePreview.get());
    m_bDrawing = false;
    m_controlPoints.clear();
    m_splinePreview->clear();
}

void OptDrawSpline::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_bDrawing)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });
        m_controlPoints.push_back(posW);
        updatePreview();
        m_viewWrap->updateRender();
    }
    else if (event->button() == Qt::RightButton && m_bDrawing)
    {
        if (m_controlPoints.size() >= 4)  // B 样条至少需要 4 个控制点
        {
            drawSpline();
        }
        m_bDrawing = false;
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
    if (m_bDrawing && !m_controlPoints.empty())
    {
        QPointF pos = event->pos();
        m_currentPoint = m_scene->screenToWorld({ pos.x(), pos.y() });
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
    if (event->key() == Qt::Key_Escape && m_bDrawing)
    {
        m_bDrawing = false;
        m_controlPoints.clear();
        m_splinePreview->clear();
        m_viewWrap->updateRender();
    }
    else if (event->key() == Qt::Key_C && m_bDrawing)  // 'C' 键切换闭合状态
    {
        m_bClosed = !m_bClosed;
        updatePreview();
        m_viewWrap->updateRender();
    }
    Super::keyPressEvent(event);
}

void OptDrawSpline::setSplineData(MEngine::CubicBSpline* spline)
{
    // 可选：设置额外的样条属性，例如颜色、层等
}

void OptDrawSpline::drawSpline()
{
    if (m_controlPoints.size() < 4)
        return;

    MEngine::CubicBSpline* spline = new MEngine::CubicBSpline();
    spline->setControlPoints(m_controlPoints, m_bClosed);
    spline->setSegmentsPerSpan(32);  // 默认每段 32 个采样点
    setSplineData(spline);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), spline);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}

void OptDrawSpline::updatePreview()
{
    if (m_controlPoints.size() < 1)
        return;

    // 创建临时的控制点列表，包括当前鼠标位置
    std::vector<Ut::Vec2d> previewPoints = m_controlPoints;
    if (m_controlPoints.size() < 4)
    {
        // 如果控制点不足 4 个，重复最后一个点以生成预览
        while (previewPoints.size() < 4)
        {
            previewPoints.push_back(m_currentPoint);
        }
    }
    else
    {
        previewPoints.push_back(m_currentPoint);
    }

    m_splinePreview->setControlPoints(previewPoints, m_bClosed);
    m_splinePreview->setSegmentsPerSpan(32);
}