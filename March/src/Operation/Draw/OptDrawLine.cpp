#include "OptDrawLine.h"

#include "Command/AddEntityCmd.h"

#include "Render/MarchView.h"
#include "Eng/Entity/Line.h"

OptDrawLine::OptDrawLine(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Line;

    m_linePreview = std::make_unique<MEngine::Line>();
    m_scene->addPreview(m_linePreview.get());
}

OptDrawLine::~OptDrawLine()
{
    m_linePreview.reset();
}

void OptDrawLine::enter()
{
    m_nPts = 0;
}

void OptDrawLine::exit()
{
    m_scene->removePreview(m_linePreview.get());
    Super::exit();
    m_nPts = 0;
}

void OptDrawLine::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        auto posW = m_scene->screenToWorld(Ut::Vec2d(pos.x(), pos.y()));
        
        // 开始绘制时直接记录起点
        m_startPoint = posW;
        m_linePreview->m_basePt = posW;
        m_linePreview->m_secPoint = posW;
        m_nPts = 1;  // 进入绘制状态
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

void OptDrawLine::mouseMoveEvent(QMouseEvent* event)
{
    if (m_nPts == 1)  // 在绘制状态下
    {
        auto pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });
        m_linePreview->m_secPoint = posW;  // 实时更新预览线终点
        m_viewWrap->updateRender();
    }

    //if (event->buttons() & Qt::LeftButton)
    //{
    //    QPointF start = m_scene->getStartPoint();
    //    QPointF end = event->pos();
    //    m_scene->updateTempLine(Ut::Vec2d(start.x(), start.y()), Ut::Vec2d(end.x(), end.y()));
    //}

    Super::mouseMoveEvent(event);
}

void OptDrawLine::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_nPts == 1)
    {
        auto pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });
        
        // 有效距离时创建直线
        if ((m_endPoint - m_startPoint).length() > 1e-6) {
            drawLine();
        }
        
        // 重置状态
        m_nPts = 0;
        m_linePreview->m_basePt = m_startPoint;
        m_linePreview->m_secPoint = m_startPoint;
        m_viewWrap->updateRender();
    }
    Super::mouseReleaseEvent(event);
}

void OptDrawLine::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawLine::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        if (m_nPts == 0)
        {
            exit();
        }
        else if (m_nPts == 1)
        {
            m_nPts = 0;
            m_linePreview->m_basePt = m_startPoint;
            m_linePreview->m_secPoint = m_startPoint;
            m_viewWrap->updateRender();
        }
    }
    Super::keyPressEvent(event);
}

void OptDrawLine::drawLine()
{
    m_nPts = 0;

    MEngine::Line* line = new MEngine::Line();
    // auto line = std::make_shared<MEngine::Line>();

    if ((m_endPoint - m_startPoint).length() < 1e-6)
        return;

    line->m_basePt = m_startPoint;
    line->m_secPoint = m_endPoint;
    // line->m_nId = i;
    // i++;

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), line);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();

    //m_scene->paint();
    //m_glView->update();
}