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
    m_scene->addPreview(m_linePreview.get());
    m_nPts = 0;
}

void OptDrawLine::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();

        auto posW = m_scene->screenToWorld(Ut::Vec2d(pos.x(), pos.y()));
        if (m_nPts == 0)
        {
            m_linePreview->m_basePt = posW;
            m_linePreview->m_secPoint = posW;

            m_startPoint = std::move(posW);
            m_nPts++;
        }
        else
        {
            m_endPoint = std::move(posW);
            drawLine();
        }
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

void OptDrawLine::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
    }

    Super::mouseReleaseEvent(event);
}

void OptDrawLine::mouseMoveEvent(QMouseEvent* event)
{
    if (m_nPts == 1)
    {
        auto pos = event->pos();
        auto posW = m_scene->screenToWorld({pos.x(), pos.y()});
        m_linePreview->m_secPoint = posW;

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

void OptDrawLine::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawLine::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {

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