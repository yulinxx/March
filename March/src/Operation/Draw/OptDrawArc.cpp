#include "OptDrawArc.h"
#include "Entity/Arc.h"
#include "Eng/Entity/Line.h"

#include "Command/AddEntityCmd.h"
#include "Render/MarchView.h"

OptDrawArc::OptDrawArc(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_drawType = DrawType::Arc;

    m_linePreview = std::make_shared<MEngine::Line>();
    m_arcPreview = std::make_shared<MEngine::Arc>();

    m_scene->addPreview(m_linePreview.get());
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
    m_nPts = 0;
    m_scene->removePreview(m_linePreview.get());
    m_scene->removePreview(m_arcPreview.get());
    m_arcPreview->clear();
}

void OptDrawArc::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPointF pos = event->pos();
        Ut::Vec2d posW = m_scene->screenToWorld({ pos.x(), pos.y() });

        if (m_nPts == 0)  // 第一个点：起点
        {
            m_linePreview->setPoints(posW, posW);  // 初始化预览线
            m_startPoint = posW;
            m_nPts = 1;
        }
        else if (m_nPts == 1)  // 第二个点：中间点
        {
            m_linePreview->clear();  // 直线预览线

            m_midPoint = posW;
            m_nPts = 2;
        }
        else if (m_nPts == 2)  // 第三个点：终点
        {
            m_linePreview->clear();
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

        m_linePreview->clear();
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
    QPointF pos = event->pos();
    auto posW = m_scene->screenToWorld({ pos.x(), pos.y() });
    if (m_nPts > 0)  // 在绘制状态下
    {
        m_endPoint = posW;
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
    arc->setSides(32);  // 32 段，控制平滑度

    auto addCmd = std::make_unique<MEngine::AddEntityCmd>(m_scene->getRootGroup(), arc);
    m_scene->execute(std::move(addCmd));

    m_viewWrap->updateRender();
}

void OptDrawArc::updatePreview()
{
    m_linePreview->clear();

    if (m_nPts == 1)  // 只有一个点时，预览为直线
    {
        m_linePreview->setPoints(m_startPoint, m_endPoint);
        m_arcPreview->setByThreePoints(m_startPoint, m_startPoint, m_endPoint);  // 退化为点
    }
    else if (m_nPts == 2)  // 有两个点时，预览圆弧
    {
        m_arcPreview->setByThreePoints(m_startPoint, m_midPoint, m_endPoint);
        //m_arcPreview->setSides(32);
    }
}