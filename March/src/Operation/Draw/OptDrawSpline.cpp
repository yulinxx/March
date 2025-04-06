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
        if (m_controlPoints.size() >= 4)  // B ����������Ҫ 4 �����Ƶ�
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
    else if (event->key() == Qt::Key_C && m_bDrawing)  // 'C' ���л��պ�״̬
    {
        m_bClosed = !m_bClosed;
        updatePreview();
        m_viewWrap->updateRender();
    }
    Super::keyPressEvent(event);
}

void OptDrawSpline::setSplineData(MEngine::CubicBSpline* spline)
{
    // ��ѡ�����ö�����������ԣ�������ɫ�����
}

void OptDrawSpline::drawSpline()
{
    if (m_controlPoints.size() < 4)
        return;

    MEngine::CubicBSpline* spline = new MEngine::CubicBSpline();
    spline->setControlPoints(m_controlPoints, m_bClosed);
    spline->setSegmentsPerSpan(32);  // Ĭ��ÿ�� 32 ��������
    setSplineData(spline);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), spline);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}

void OptDrawSpline::updatePreview()
{
    if (m_controlPoints.size() < 1)
        return;

    // ������ʱ�Ŀ��Ƶ��б�������ǰ���λ��
    std::vector<Ut::Vec2d> previewPoints = m_controlPoints;
    if (m_controlPoints.size() < 4)
    {
        // ������Ƶ㲻�� 4 �����ظ����һ����������Ԥ��
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