#include "OptBase.h"

#include "Render/MarchView.h"
#include "Widgets/RenderView/ViewWrapper.h"

#include <QDateTime>
#include <QApplication>

#include <algorithm>
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
        m_selectStart = m_scene->screenToWorld({ event->pos().x(), event->pos().y() });
        m_selectEnd = m_selectStart;
        m_bSelecting = true;

        // 清除之前的选择
        //m_scene->clearSelection();
        //m_glView->update();

        if (0)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> disColor(0.0f, 1.0f);
            float r = disColor(gen);
            float g = disColor(gen);
            float b = disColor(gen);

            auto world = m_scene->screenToWorld({ event->pos().x(), event->pos().y() });

            m_glView->addLinePoint({ float(world.x()), float(world.y()), 0.0f, r, g, b });
            m_glView->update();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        if (0)
        {

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> disColor(0.0f, 1.0f);

            Ut::Vec2d sz = m_scene->getViewSize();
            float aspect = float(sz.x() / sz.y());

            Ut::Vec2d center = m_scene->getViewCenter();

            float dScale = m_scene->getViewScale();

            std::uniform_real_distribution<float> disX(center.x() - (sz.x() * 0.5), center.x() + (sz.x() * 0.5));
            std::uniform_real_distribution<float> disY(center.y() - (sz.y() * 0.5), center.y() + (sz.y() * 0.5));

            for (int i = 0; i < 100; ++i)
            {
                float randomX = disX(gen);
                float randomY = disY(gen);
                float r = disColor(gen);
                float g = disColor(gen);
                float b = disColor(gen);
                m_glView->addLinePoint({ randomX, randomY, 0.0f, r, g, b });
            }
            m_glView->update();
        }

    }
    else if (event->button() == Qt::MiddleButton)
    {
        m_lastPos = event->pos();
    }
}

void OptBase::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_bSelecting)
    {
        // 计算选择区域
        Ut::Vec2d minPt(
            std::min(m_selectStart.x(), m_selectEnd.x()),
            std::min(m_selectStart.y(), m_selectEnd.y())
        );

        Ut::Vec2d maxPt(
            std::max(m_selectStart.x(), m_selectEnd.x()),
            std::max(m_selectStart.y(), m_selectEnd.y())
        );

        // 判断选择方向
        bool bCrossSel = (m_selectEnd.x() < m_selectStart.x());

        // 执行选择
        if (bCrossSel)
        {
            qDebug() << "Cross selection";
            //m_scene->selectByCross(minPt, maxPt); // 交选
        }
        else
        {
            qDebug() << "Window selection";
            //m_scene->selectByWindow(minPt, maxPt); // 窗选
        }

        m_bSelecting = false;
        m_glView->update();
    }
    else if (event->button() == Qt::MiddleButton)
    {
        m_bPanning = false;
    }
}

void OptBase::mouseMoveEvent(QMouseEvent* event)
{
    QPoint curPos = event->pos();
    auto world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

    if (m_bSelecting && (event->buttons() & Qt::LeftButton))
    {
        m_selectEnd = world;
    }
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
    auto world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

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
        m_viewWrap->setOperation(0);
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