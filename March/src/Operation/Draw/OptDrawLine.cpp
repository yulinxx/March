#include "OptDrawLine.h"
#include "Eng/Entity/Line.h"

OptDrawLine::OptDrawLine(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Line;
    m_linePreview = std::make_shared<MEngine::Line>();
    m_scene->addPreview(m_linePreview.get());
}

OptDrawLine::~OptDrawLine()
{
    m_linePreview.reset();
}

void OptDrawLine::enter()
{
    m_bFirst = true;
}

void OptDrawLine::exit()
{
    m_scene->removePreview(m_linePreview.get());
    m_bFirst = true;
}

void OptDrawLine::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        if (m_bFirst)
        {
            m_startPoint = posW;

            m_linePreview->setLayer(m_scene->getLayerManager()->getCurrentLayer());
            m_linePreview->setPoints(posW, posW);  // 初始化预览线
            m_bFirst = false;
        }
    }
    else if (event->button() == Qt::MiddleButton || event->button() == Qt::RightButton)
    {
        Super::mousePressEvent(event);
    }
}

void OptDrawLine::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_bFirst)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });
        m_linePreview->setEndPoint(posW);  // 更新预览终点
        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawLine::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !m_bFirst)
    {
        QPointF pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });

        if ((m_endPoint - m_startPoint).length() < 1e-3)
            return;

        drawLine();
        m_bFirst = true;
        //m_linePreview->setPoints(m_startPoint, m_startPoint);  // 重置预览线
        m_linePreview->clear();
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
        if (m_bFirst)
        {
            exit();
        }
        else
        {
            m_bFirst = true;
        }

        m_linePreview->clear();
        m_viewWrap->updateRender();

    }
    Super::keyPressEvent(event);
}

void OptDrawLine::drawLine()
{
    MEngine::Line* line = new MEngine::Line();
    line->setPoints(m_startPoint, m_endPoint);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, line);
    m_scene->execute(std::move(addCmd));

    m_bFirst = true;  // 重置状态
    m_viewWrap->updateRender();
}