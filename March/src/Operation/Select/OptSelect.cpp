#include "OptSelect.h"
#include "Ut/Matrix.h"

#include "Eng/Command/TransformCmd.h"
#include "Eng/Entity/Rectangle.h"
#include "Command/DelEntityCmd.h"

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
    if (event->button() == Qt::LeftButton)
    {
        m_posStart = m_scene->screenToWorld({ event->pos().x(), event->pos().y() });

        auto sz = m_scene->getSelectSz();
        if(sz)
        {
            m_bSelecting = false;
            m_bMoving = true;
        }
        else
        {
            // 记录选择起始点
            m_posEnd = m_posStart;

            m_rectPreview->clear();
            m_rectPreview->setLayer(m_scene->getLayerManager()->getCurrentLayer());
            m_viewWrap->updateRender();

            m_bSelecting = true;
            m_bMoving = false;
        }
    }
    if (event->button() == Qt::MiddleButton)
    {

    }
    else if (event->button() == Qt::RightButton)
    {
    }


    Super::mousePressEvent(event);
}

//DrawType OptSelect::getDrawType()
//{
//    return m_drawType;
//}

void OptSelect::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint curPos = event->pos();
        Ut::Vec2d currentPos = m_scene->screenToWorld({ curPos.x(), curPos.y() });

        if (m_bSelecting)
        {
            m_posEnd = currentPos;
    
            m_rectPreview->setPts(m_posStart, m_posEnd);
            m_viewWrap->updateRender();
        }
        else if (m_bMoving)
        {
            std::vector<std::shared_ptr<MEngine::Entity>> entities;
            m_scene->getSelectedEntities(entities);
            
            if (!entities.empty())
            {
                Ut::Vec2d delta = currentPos - m_posStart;
                
                Ut::Mat3 transform;
                transform.translation(delta);
                
                auto cmd = std::make_unique<MEngine::TransformCmd>(m_scene, entities, transform);
                m_scene->execute(std::move(cmd));
                
                m_posEnd = currentPos;
                m_viewWrap->updateRender();
            }
        }
    }

    Super::mouseMoveEvent(event);
}

void OptSelect::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(m_bSelecting)
        {
            // 计算选择区域
            Ut::Vec2d minPt(
                std::min(m_posStart.x(), m_posEnd.x()),
                std::min(m_posStart.y(), m_posEnd.y())
            );

            Ut::Vec2d maxPt(
                std::max(m_posStart.x(), m_posEnd.x()),
                std::max(m_posStart.y(), m_posEnd.y())
            );

            // 判断选择方向
            bool bCrossSel = (m_posEnd.x() < m_posStart.x());

            if (bCrossSel)
            {
                m_scene->selectByRect(minPt, maxPt); // 交选
            }
            else
            {
                m_scene->selectByRect(minPt, maxPt); // 窗选
            }

            //m_rectPreview->setPts(m_posStart, m_posEnd);
            m_rectPreview->clear();

            m_bSelecting = false;

            m_viewWrap->updateRender();

            emit m_viewWrap->sigSelChanged(m_scene->getSelectSz());
        }
        else if(m_bMoving)
        {
            std::vector<std::shared_ptr<MEngine::Entity>> entities;
            m_scene->getSelectedEntities(entities);

            Ut::Mat3 transform;
            Ut::Vec2d delta = m_posStart - m_posEnd;
            transform.translation(delta);

            auto moveCmd = std::make_unique<MEngine::TransformCmd>(
                m_scene, entities, transform);
        }
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


void OptSelect::mouseDoubleClickEvent(QMouseEvent* event)
{
    Super::mouseDoubleClickEvent(event);
}

void OptSelect::wheelEvent(QWheelEvent* event)
{
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
