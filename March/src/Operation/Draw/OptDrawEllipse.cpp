#include "OptDrawEllipse.h"
#include "Entity/Ellipse.h"

OptDrawEllipse::OptDrawEllipse(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Ellipse;

    m_ellipsePreview = std::make_shared<MEngine::Ellipse>();
    m_scene->addPreview(m_ellipsePreview.get());
}

OptDrawEllipse::~OptDrawEllipse()
{
}

void OptDrawEllipse::enter()
{
    m_drawType = DrawType::Ellipse;
}

void OptDrawEllipse::exit()
{
    m_scene->removePreview(m_ellipsePreview.get());
    m_bFirst = true;
}

void OptDrawEllipse::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        if (m_bFirst)
        {
            m_centerPoint = posW;  // ��һ�ε���������ĵ�
            m_bFirst = false;
        }
    }
    else if (event->button() == Qt::MiddleButton || event->button() == Qt::RightButton)
    {
        Super::mousePressEvent(event);
    }
}

void OptDrawEllipse::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_bFirst)
    {
        QPointF pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });

        // ���㳤��Ͷ���
        double dx = fabs(m_endPoint.x() - m_centerPoint.x());
        double dy = fabs(m_endPoint.y() - m_centerPoint.y());
        double majorRadius = std::max(dx, dy);  // ����ȡ�ϴ�ֵ
        double minorRadius = std::min(dx, dy);  // ����ȡ��Сֵ
        double rotation = (dx > dy) ? 0.0 : Ut::PI / 2.0;  // ���ݷ��������ת

        m_ellipsePreview->setByCenterAxes(m_centerPoint, majorRadius, minorRadius, rotation);
        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawEllipse::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !m_bFirst)
    {
        double distance = (m_endPoint - m_centerPoint).length();
        if (distance > 1e-3)
        {
            drawEllipse();
        }

        m_bFirst = true;
        m_ellipsePreview->clear();
        m_viewWrap->updateRender();
    }

    Super::mouseReleaseEvent(event);
}

void OptDrawEllipse::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawEllipse::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_bFirst = true;
        m_ellipsePreview->clear();
        m_viewWrap->updateRender();
    }
    Super::keyPressEvent(event);
}

void OptDrawEllipse::setEllipseData(MEngine::Ellipse* ellipse)
{
    // ��ѡ�����ö������Բ���ԣ�������ɫ�����
}

void OptDrawEllipse::drawEllipse()
{
    m_bFirst = true;
    if ((m_endPoint - m_centerPoint).length() < 1e-3)
        return;

    MEngine::Ellipse* ellipse = new MEngine::Ellipse();
    double dx = fabs(m_endPoint.x() - m_centerPoint.x());
    double dy = fabs(m_endPoint.y() - m_centerPoint.y());
    double majorRadius = std::max(dx, dy);
    double minorRadius = std::min(dx, dy);
    double rotation = (dx > dy) ? 0.0 : Ut::PI / 2.0;

    ellipse->setByCenterAxes(m_centerPoint, majorRadius, minorRadius, rotation);
    ellipse->setSides(64);
    setEllipseData(ellipse);

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene, ellipse);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}