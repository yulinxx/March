#include "OptSelect.h"
#include "Ut/Matrix.h"

#include "Eng/Command/TransformCmd.h"
#include "Command/DelEntityCmd.h"

#include "Eng/Entity/Rectangle.h"

OptSelect::OptSelect(MEngine::Scene* scene)
    : OptBase(scene)
{
    m_rectPreview = std::make_unique<MEngine::Rectangle>();
    m_scene->addPreview(m_rectPreview.get());
}

OptSelect::~OptSelect()
{
}

void OptSelect::enter()
{
}

void OptSelect::exit()
{
    m_scene->removePreview(m_rectPreview.get());
}

void OptSelect::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        // m_lastPanPos = event->pos();
        // m_bPanning = true;

        // if (1)
        // {
        //     qint64 curTime = QDateTime::currentMSecsSinceEpoch();
        //     if (curTime - m_lastMiddleClickTime < QApplication::doubleClickInterval()
        //         && (event->pos() - m_lastMiddlePos).manhattanLength() < 5)
        //     {
        //         resetView();
        //         return;
        //     }

        //     m_lastMiddleClickTime = curTime;
        //     m_lastMiddlePos = event->pos();
        //     m_lastPos = event->pos();
        // }
    }
    else if (event->button() == Qt::LeftButton)
    {
        // 记录选择起始点
        m_selectStart = m_scene->screenToWorld({ event->pos().x(), event->pos().y() });
        m_selectEnd = m_selectStart;

        m_rectPreview->clear();
        m_rectPreview->setLayer(m_scene->getLayerManager()->getCurrentLayer());
        m_viewWrap->updateRender();

        m_bSelecting = true;
    }
    else if (event->button() == Qt::RightButton)
    {
    }
    else if (event->button() == Qt::MiddleButton)
    {
        // m_lastPos = event->pos();
    }
}

//DrawType OptSelect::getDrawType()
//{
//    return m_drawType;
//}

void OptSelect::mouseReleaseEvent(QMouseEvent* event)
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
            m_scene->selectByRect(minPt, maxPt); // 交选
        }
        else
        {
            m_scene->selectByRect(minPt, maxPt); // 窗选
        }

        //m_rectPreview->setPts(m_selectStart, m_selectEnd);
        m_rectPreview->clear();

        m_bSelecting = false;

        m_viewWrap->updateRender();
    }
    else if (event->button() == Qt::MiddleButton)
    {
        // m_bPanning = false;
        m_rectPreview->clear();
        m_viewWrap->updateRender();
    }
    else
    {
        m_rectPreview->clear();
        m_viewWrap->updateRender();
    }
}

void OptSelect::mouseMoveEvent(QMouseEvent* event)
{
    if (m_bSelecting && (event->buttons() & Qt::LeftButton))
    {
        QPoint curPos = event->pos();
        Ut::Vec2d world = m_scene->screenToWorld({ curPos.x(), curPos.y() });
        m_selectEnd = world;

        m_rectPreview->setPts(m_selectStart, m_selectEnd);
        m_viewWrap->updateRender();
    }

    //if (event->buttons() & Qt::MiddleButton)
    //{
        // if (m_bPanning)
        // {
        //     auto posA = m_scene->screenToWorld({ m_lastPanPos.x(), m_lastPanPos.y() });
        //     auto dir = world - posA;

        //     m_scene->pan(dir);

        //     auto& mat = m_scene->getViewMatrix();
        //     m_glView->setViewMatrix(mat);

        //     m_lastPanPos = curPos;
        // }
    //}

    //m_viewWrap->set
}

void OptSelect::mouseDoubleClickEvent(QMouseEvent* event)
{
}

void OptSelect::wheelEvent(QWheelEvent* event)
{
    // QPointF curPos = event->position();
    // Ut::Vec2d world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

    // float delta = event->angleDelta().y() > 0 ? 1.1f : 0.9f;

    // // 中心点缩放
    // m_scene->zoomAt(Ut::Vec2{ world.x(), world.y() }, delta);
    // // 视图中心点缩放
    // //m_scene->setZoom(delta);

    // Ut::Mat3& matView = m_scene->getViewMatrix();
    // m_glView->setViewMatrix(matView);

    // m_glView->update();

    //sigCoordChanged(world.x(), world.y());
}

void OptSelect::keyPressEvent(QKeyEvent* event)
{
    std::vector<std::shared_ptr<MEngine::Entity>> entities;
    m_scene->getSelectedEntities(entities);

    if (entities.empty())
        return;

    if (event->key() == Qt::Key_Escape)
    {
        // 清空当前选择
        m_scene->clearSelection();
        m_viewWrap->updateRender();
    }
    else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
    {
        auto delCmd = std::make_unique<MEngine::DelEntityCmd>(m_scene, entities);
        m_scene->execute(std::move(delCmd));
        m_viewWrap->updateRender();
    }
    else if (event->key() >= Qt::Key_Left && event->key() <= Qt::Key_Down)
    {
        const double moveStep = 1.0;
        const double rotateStep = 5.0;
        const double scaleStep = 0.1;

        // 计算所有选中实体的中心点
        Ut::Vec2d center(0, 0);
        Ut::Rect2d rect;
        for (const auto& entity : entities)
        {
            rect.expand(entity->getRect());
        }

        center /= entities.size();

        Ut::Mat3 transform;

        double dAngle = 1.0;
        if (event->modifiers() & Qt::ShiftModifier)
        {
            // 以中心点旋转
            transform.translation(-center);
            double dR = dAngle * Ut::PI / 180.0;
            transform.rotation(dR);

            //transform.translate(center);
            transform.translation(center);
        }
        else if (event->modifiers() & Qt::ControlModifier)
        {
            // 以中心点缩放
            double scale = (event->key() == Qt::Key_Left || event->key() == Qt::Key_Down)
                ? 1.0 - scaleStep : 1.0 + scaleStep;
            transform.translation(-center);
            if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
            {
                transform.scale(scale, 1.0);
            }
            else
            {
                transform.scale(1.0, scale);
            }
            transform.translation(center);
        }
        else
        {
            // 移动
            Ut::Vec2d delta(0, 0);
            switch (event->key())
            {
            case Qt::Key_Left:  delta.x() = -moveStep; break;
            case Qt::Key_Right: delta.x() = moveStep; break;
            case Qt::Key_Up:    delta.y() = moveStep; break;
            case Qt::Key_Down:  delta.y() = -moveStep; break;
            }
            transform.translation(delta);
        }

        auto cmd = std::make_unique<MEngine::TransformCmd>(m_scene, entities, transform);
        m_scene->execute(std::move(cmd));
        m_viewWrap->updateRender();
    }
}

void OptSelect::keyReleaseEvent(QKeyEvent* event)
{
}

void OptSelect::resizeEvent(QResizeEvent* event)
{
}

void OptSelect::enterEvent(QEnterEvent* event)
{
}

void OptSelect::leaveEvent(QEvent* event)
{
}

//void OptSelect::resetView()
//{
//    auto sz = m_glView->size();
//    m_scene->setView(sz.width(), sz.height());
//
//    auto& mat = m_scene->getViewMatrix();
//    m_glView->clearLinePoints();
//    m_glView->setViewMatrix(mat);
//    m_glView->update();
//}

//void OptSelect::setViewWidget(ViewWrapper* parent)
//{
//    m_viewWrap = parent;
//}
//
//void OptSelect::setGLView(MRender::MarchView* glView)
//{
//    m_glView = glView;
//}