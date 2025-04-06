#include "OptDrawArc.h"
#include "Entity/Arc.h"
#include "Command/AddEntityCmd.h"
#include "Render/MarchView.h"

OptDrawArc::OptDrawArc(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Arc;

    m_arcPreview = std::make_shared<MEngine::Arc>();
    m_scene->addPreview(m_arcPreview.get());
}

OptDrawArc::~OptDrawArc()
{
    m_arcPreview.reset();
}

void OptDrawArc::enter()
{
    m_drawType = DrawType::Arc;
    m_nPts = 0;
}

void OptDrawArc::exit()
{
    m_scene->removePreview(m_arcPreview.get());
    m_nPts = 0;
    m_arcPreview->clear();
}

void OptDrawArc::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        if (m_nPts == 0)  // ��һ���㣺���
        {
            m_startPoint = posW;
            m_nPts = 1;
        }
        else if (m_nPts == 1)  // �ڶ����㣺�м��
        {
            m_midPoint = posW;
            m_nPts = 2;
        }
        else if (m_nPts == 2)  // �������㣺�յ�
        {
            m_endPoint = posW;
            if ((m_startPoint - m_midPoint).length() > 1e-3 &&
                (m_midPoint - m_endPoint).length() > 1e-3 &&
                (m_startPoint - m_endPoint).length() > 1e-3)
            {
                drawArc();
            }
            m_nPts = 0;
            m_arcPreview->clear();
            m_viewWrap->updateRender();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        m_nPts = 0;
        m_arcPreview->clear();
        m_viewWrap->updateRender();
    }
    else
    {
        Super::mousePressEvent(event);
    }
}

void OptDrawArc::mouseReleaseEvent(QMouseEvent* event)
{
    Super::mouseReleaseEvent(event);
}

void OptDrawArc::mouseMoveEvent(QMouseEvent* event)
{
    if (m_nPts > 0)  // �ڻ���״̬��
    {
        QPointF pos = event->pos();
        m_endPoint = m_scene->screenToWorld({ pos.x(), pos.y() });

        updatePreview();
        m_viewWrap->updateRender();
    }

    Super::mouseMoveEvent(event);
}

void OptDrawArc::wheelEvent(QWheelEvent* event)
{
    Super::wheelEvent(event);
}

void OptDrawArc::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_nPts = 0;
        m_arcPreview->clear();
        m_viewWrap->updateRender();
    }
    Super::keyPressEvent(event);
}

void OptDrawArc::drawArc()
{
    MEngine::Arc* arc = new MEngine::Arc();
    arc->setByThreePoints(m_startPoint, m_midPoint, m_endPoint);
    arc->setSides(32);  // Ĭ�� 32 �Σ�����ƽ����

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), arc);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}

void OptDrawArc::updatePreview()
{
    if (m_nPts == 1)  // ֻ��һ����ʱ��Ԥ��Ϊֱ��
    {
        m_arcPreview->setByThreePoints(m_startPoint, m_startPoint, m_endPoint);  // �˻�Ϊ��
    }
    else if (m_nPts == 2)  // ��������ʱ��Ԥ��Բ��
    {
        m_arcPreview->setByThreePoints(m_startPoint, m_midPoint, m_endPoint);
        m_arcPreview->setSides(32);
    }
}