#include "OptDrawCircle.h"

#include "Eng/Entity/Circle.h"
#include "Command/AddEntityCmd.h"

OptDrawCircle::OptDrawCircle(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Circle;

    m_circlePreview = std::make_unique<MEngine::Circle>();
    m_scene->addPreview(m_circlePreview.get());
}

OptDrawCircle::~OptDrawCircle()
{
}

void OptDrawCircle::enter()
{
    m_drawType = DrawType::Circle;
}

void OptDrawCircle::exit()
{
    m_scene->removePreview(m_circlePreview.get());
    m_bFirst = false;
}

void OptDrawCircle::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        m_startPoint = posW;
        m_circlePreview->setLayer(m_scene->getLayerManager()->getCurrentLayer());
        m_circlePreview->setBasePoint(posW);
        m_bFirst = false;
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

void OptDrawCircle::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_bFirst)
    {
        QPointF pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });

        setCircleData(m_circlePreview.get());

        m_circlePreview->setByCenterPt(m_startPoint, m_endPoint);

        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawCircle::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        double distance = (m_endPoint - m_startPoint).length();

        if (distance > 1e-3)
        {
            drawCircle();
        }

        m_bFirst = true;
        m_circlePreview->clear();
        m_viewWrap->updateRender();
    }

    Super::mouseReleaseEvent(event);
}

void OptDrawCircle::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawCircle::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_bFirst = true;
    }
    Super::keyPressEvent(event);
}

void OptDrawCircle::setCircleData(MEngine::Circle* circle)
{
}

void OptDrawCircle::drawCircle()
{
    m_bFirst = true;
    if ((m_endPoint - m_startPoint).length() < 1e-3)
        return;

    MEngine::Circle* circle = new MEngine::Circle();
    //setCircleData(circle);
    circle->setByCenterPt(m_startPoint, m_endPoint);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, circle);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}