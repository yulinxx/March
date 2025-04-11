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

    Super::mousePressEvent(event);
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

        if (bCrossSel)
        {
            m_scene->selectByRect(minPt, maxPt); // 交选
        }
        else
        {
            m_scene->selectByRect(minPt, maxPt); // 窗选
        }

        m_rectPreview->clear();

        m_bSelecting = false;

        m_viewWrap->updateRender();

        emit m_viewWrap->sigSelChanged(m_scene->getSelectSz());
    }
    else if (event->button() == Qt::MiddleButton)
    {
        m_rectPreview->clear();
        m_viewWrap->updateRender();
    }
    else
    {
        m_rectPreview->clear();
        m_viewWrap->updateRender();
    }

    Super::mouseReleaseEvent(event);

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

    Super::mouseMoveEvent(event);

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
    Super::mouseDoubleClickEvent(event);
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

    Super::wheelEvent(event);
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

        // 修正中心点计算：使用包围盒中心
        Ut::Rect2d rect;
        for (const auto& entity : entities)
        {
            rect.expand(entity->getRect());
        }

        Ut::Vec2d center = rect.getCenter();

        Ut::Mat3 transform;

        if (event->modifiers() & Qt::ShiftModifier)
        {
            // 根据方向键设置旋转方向
            double dR = rotateStep * Ut::PI / 180.0;
            if (event->key() == Qt::Key_Right) dR *= -1; // 右键顺时针
            else if (event->key() == Qt::Key_Left) dR *= 1; // 左键逆时针

            // 围绕中心旋转的变换矩阵
            transform.translation(-center);
            transform.rotation(dR);
            transform.translation(center);;
        }
        else if (event->modifiers() & Qt::ControlModifier)
        {
            // 统一缩放逻辑
            double scaleX = 1.0;
            double scaleY = 1.0;

            // 根据按键设置缩放方向和轴
            if (event->key() == Qt::Key_Left)  scaleX = 1.0 - scaleStep;
            if (event->key() == Qt::Key_Right) scaleX = 1.0 + scaleStep;
            if (event->key() == Qt::Key_Up)    scaleY = 1.0 + scaleStep;
            if (event->key() == Qt::Key_Down)  scaleY = 1.0 - scaleStep;

            // 围绕中心缩放的变换矩阵
            transform.translation(-center);
            transform.scale(scaleX, scaleY);
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
    Super::keyPressEvent(event);
}

void OptSelect::keyReleaseEvent(QKeyEvent* event)
{
    Super::keyReleaseEvent(event);
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