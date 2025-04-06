#include "OptDrawCubicBezier.h"
#include "Entity/CubicBezier.h"
#include "Command/AddEntityCmd.h"

OptDrawCubicBezier::OptDrawCubicBezier(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::CubicBezier;

    m_bezierPreview = std::make_shared<MEngine::CubicBezier>();
    m_scene->addPreview(m_bezierPreview.get());
}

OptDrawCubicBezier::~OptDrawCubicBezier()
{
}

void OptDrawCubicBezier::enter()
{
    m_drawType = DrawType::CubicBezier;
    m_bDrawing = true;
    m_controlPoints.clear();
}

void OptDrawCubicBezier::exit()
{
    m_scene->removePreview(m_bezierPreview.get());
    m_bDrawing = false;
    m_controlPoints.clear();
    m_bezierPreview->clear();
}

void OptDrawCubicBezier::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_bDrawing)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        if (m_controlPoints.size() < 4)
        {
            m_controlPoints.push_back(posW);
            updatePreview();

            if (m_controlPoints.size() == 4)  // 第 4 个点完成绘制
            {
                drawBezier();
                m_bDrawing = false;
                m_controlPoints.clear();
                m_bezierPreview->clear();
            }

            m_viewWrap->updateRender();
        }
    }
    else if (event->button() == Qt::RightButton && m_bDrawing)
    {
        m_bDrawing = false;
        m_controlPoints.clear();
        m_bezierPreview->clear();
        m_viewWrap->updateRender();
    }
    else
    {
        Super::mousePressEvent(event);
    }
}

void OptDrawCubicBezier::mouseReleaseEvent(QMouseEvent* event)
{
    Super::mouseReleaseEvent(event);
}

void OptDrawCubicBezier::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bDrawing && !m_controlPoints.empty() && m_controlPoints.size() < 4)
    {
        QPointF pos = event->pos();
        m_currentPoint = m_scene->screenToWorld({ pos.x(), pos.y() });
        updatePreview();
        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawCubicBezier::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawCubicBezier::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape && m_bDrawing)
    {
        m_bDrawing = false;
        m_controlPoints.clear();
        m_bezierPreview->clear();
        m_viewWrap->updateRender();
    }
    Super::keyPressEvent(event);
}

void OptDrawCubicBezier::setBezierData(MEngine::CubicBezier* bezier)
{
    // 可选：设置额外的贝塞尔属性，例如颜色、层等
}

void OptDrawCubicBezier::drawBezier()
{
    if (m_controlPoints.size() != 4)
        return;

    MEngine::CubicBezier* bezier = new MEngine::CubicBezier();
    bezier->setByControlPoints(
        m_controlPoints[0],
        m_controlPoints[1],
        m_controlPoints[2],
        m_controlPoints[3]
    );
    bezier->setSegments(32);  // 默认 32 个采样点
    setBezierData(bezier);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), bezier);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}

void OptDrawCubicBezier::updatePreview()
{
    if (m_controlPoints.empty())
        return;

    // 创建临时的控制点列表，包括当前鼠标位置
    std::vector<Ut::Vec2d> previewPoints = m_controlPoints;
    while (previewPoints.size() < 4)
    {
        previewPoints.push_back(m_currentPoint);  // 用当前点填充不足的控制点
    }

    m_bezierPreview->setByControlPoints(
        previewPoints[0],
        previewPoints[1],
        previewPoints[2],
        previewPoints[3]
    );
    m_bezierPreview->setSegments(32);
}