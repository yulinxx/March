#include "OptBase.h"

#include "Render/MarchView.h"
#include "Widgets/RenderView/ViewWrapper.h"

#include <QDateTime>
#include <QApplication>

#include <algorithm>
#include "def.h"
#include <random>

OptBase::OptBase(MEngine::Scene* scene)
    : m_scene(scene)
{
}

OptBase::~OptBase()
{
}

void OptBase::enter()
{
}

void OptBase::exit()
{
    if (m_viewWrap)
        m_viewWrap->setOperation(static_cast<int>(DrawType::Select));
}

void OptBase::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        m_lastPanPos = event->pos();
        m_bPanning = true;

        if (1)
        {
            qint64 curTime = QDateTime::currentMSecsSinceEpoch();
            if (curTime - m_lastMiddleClickTime < QApplication::doubleClickInterval()
                && (event->pos() - m_lastMiddlePos).manhattanLength() < 5)
            {
                resetView();
                return;
            }

            m_lastMiddleClickTime = curTime;
            m_lastMiddlePos = event->pos();
            m_lastPos = event->pos();
        }
    }
    else if (event->button() == Qt::LeftButton)
    {
        // 记录选择起始点
    }
    else if (event->button() == Qt::RightButton)
    {
    }
    else if (event->button() == Qt::MiddleButton)
    {
        m_lastPos = event->pos();
    }
}

DrawType OptBase::getDrawType()
{
    return m_drawType;
}

void OptBase::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
    }
    else if (event->button() == Qt::MiddleButton)
    {
        m_bPanning = false;
    }
}

void OptBase::mouseMoveEvent(QMouseEvent* event)
{
    QPoint curPos = event->pos();
    Ut::Vec2d world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

    if (event->buttons() & Qt::MiddleButton)
    {
        if (m_bPanning)
        {
            auto posA = m_scene->screenToWorld({ m_lastPanPos.x(), m_lastPanPos.y() });
            auto dir = world - posA;

            m_scene->pan(dir);

            auto& mat = m_scene->getViewMatrix();
            m_glView->setViewMatrix(mat);

            m_lastPanPos = curPos;
        }
    }
}

void OptBase::mouseDoubleClickEvent(QMouseEvent* event)
{
}

void OptBase::wheelEvent(QWheelEvent* event)
{
    QPointF curPos = event->position();
    Ut::Vec2d world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

    float delta = event->angleDelta().y() > 0 ? 1.1f : 0.9f;

    // 中心点缩放
    m_scene->zoomAt(Ut::Vec2{ world.x(), world.y() }, delta);
    // 视图中心点缩放
    //m_scene->setZoom(delta);

    Ut::Mat3& matView = m_scene->getViewMatrix();
    m_glView->setViewMatrix(matView);

    m_glView->update();

    //sigCoordChanged(world.x(), world.y());
}

void OptBase::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        m_bPanning = false;
        m_viewWrap->setOperation(static_cast<int>(DrawType::Select));
    }
    if (event->key() == Qt::Key_Delete)
    {
        m_glView->clearLinePoints();
        m_glView->update();
    }
}

void OptBase::keyReleaseEvent(QKeyEvent* event)
{
}

void OptBase::resizeEvent(QResizeEvent* event)
{
}

void OptBase::enterEvent(QEnterEvent* event)
{
}

void OptBase::leaveEvent(QEvent* event)
{
}

void OptBase::resetView()
{
    auto sz = m_glView->size();
    m_scene->setView(sz.width(), sz.height());

    auto& mat = m_scene->getViewMatrix();
    m_glView->clearLinePoints();
    m_glView->setViewMatrix(mat);
    m_glView->update();
}

void OptBase::setViewWidget(ViewWrapper* parent)
{
    m_viewWrap = parent;
}

void OptBase::setGLView(MRender::MarchView* glView)
{
    m_glView = glView;
}