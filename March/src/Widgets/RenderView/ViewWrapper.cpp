#include "ViewWrapper.h"

#include <algorithm>
//#include <random>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDateTime>
#include <QApplication>
#include <QDebug>

#include "Entity/Line.h"
#include "DrawData/LineData.h"
#include "Operation/OptManager.h"

ViewWrapper::ViewWrapper(QWidget* parent) : QWidget(parent)
{
    m_scene = new MEngine::Scene();

    m_scene->setRefreshCallback([this]() { updateRender(); });
    //m_scene->setRenderVidget(m_glView);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_glView = new MRender::MarchView(this);
    layout->addWidget(m_glView);
    m_glView->installEventFilter(this);

    setLayout(layout);

    m_optManager = std::make_shared<OptManager>(this, m_scene, m_glView);

    // setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

ViewWrapper::~ViewWrapper()
{
}

void ViewWrapper::resetView()
{
    // m_optManager->resetView();
    //auto sz = m_glView->size();
    //m_scene->setView(sz.width(), sz.height());

    auto& mat = m_scene->getViewMatrix();
    m_glView->clearLinePoints();
    m_glView->setViewMatrix(mat);
    m_glView->update();
}

//const std::vector<MRender::ColorPoint>& ViewWrapper::getLinePoints() const
//{
//    return m_glView->getLinePoints();
//}

MRender::MarchView* ViewWrapper::getGlView() const
{
    return m_glView;
}

MEngine::Scene* ViewWrapper::getScene()
{
    return m_scene;
}

void ViewWrapper::updateRender()
{
    m_scene->paint();

    m_glView->clearLinePoints();
    m_glView->clearLinesPoints();

    //m_scene->getDrawData()->clear();

    if (1)
    {
        auto pairLinesData = m_scene->getDrawData()->getLineData();
        float* ptLines = pairLinesData.first;
        size_t szLines = pairLinesData.second;

        //for (size_t i = 0; i < szLines; i += 2)
        //{
        //    MRender::ColorPoint pt{ *(ptLines + i), *(ptLines + i + 1), 0.0f, 1.0f, 0.0f, 0.0f };
        //}

        m_glView->addLineData(ptLines, szLines);
    }

    if (1)
    {
        auto pairLinesData = m_scene->getDrawData()->getPreviewData();
        float* ptLines = pairLinesData.first;
        size_t szLines = pairLinesData.second;

        //for (size_t i = 0; i < szLines; i += 2)
        //{
        //    MRender::ColorPoint pt{ *(ptLines + i), *(ptLines + i + 1), 0.0f, 1.0f, 0.0f, 0.0f };
        //}

        m_glView->addLinePreview(ptLines, szLines);
    }


    if (1)
    {
        auto pairLinesData = m_scene->getDrawData()->getLinesData();
        float* ptLines = pairLinesData.first;
        size_t szLines = pairLinesData.second;

        auto pairLinesIndex = m_scene->getDrawData()->getLinesIndex();
        const unsigned int* ptIndex = pairLinesIndex.first;
        size_t szIndex = pairLinesIndex.second;

        m_glView->addLinesData(ptLines, szLines);
        m_glView->addLinesIndex(ptIndex, szIndex);

        //for (size_t i = 0; i < szLines; i += 6)
        //{
        //    MRender::ColorPoint pt{ *(ptLines + i), *(ptLines + i + 1),  *(ptLines + i + 2),
        //        *(ptLines + i + 3),*(ptLines + i + 4),*(ptLines + i + 5) };

        //    m_glView->addLinesPoint(pt);
        //}
    }

    if (1)
    {
        auto pairPreviewData = m_scene->getDrawData()->getPreviewData();
        float* ptPreview = pairPreviewData.first;
        size_t szPreview = pairPreviewData.second;

        //for (size_t i = 0; i < szPreview; i += 2)
        //{
        //    MRender::ColorPoint pt{ *(ptPreview + i), *(ptPreview + i + 1), 0.0f, 1.0f, 0.0f, 0.0f };
        //    m_glView->addLinePoint(pt);
        //}

        m_glView->addLinePreview(ptPreview, szPreview);
    }

    if (0)
    {
        auto pairPreviewData = m_scene->getDrawData()->getPreviewsData();
        float* ptPreview = pairPreviewData.first;
        size_t szPreview = pairPreviewData.second;

        for (size_t i = 0; i < szPreview; i += 6)
        {
            MRender::ColorPoint pt{ *(ptPreview + i), *(ptPreview + i + 1),  *(ptPreview + i + 2),
                *(ptPreview + i + 3),*(ptPreview + i + 4),*(ptPreview + i + 5) };

            m_glView->addLinesPoint(pt);
        }
    }

    if (1)
    {
        auto pairPreviewData = m_scene->getDrawData()->getPreviewsData();
        float* ptLines = pairPreviewData.first;
        size_t szLines = pairPreviewData.second;

        auto pairPreviewIndex = m_scene->getDrawData()->getPreviewsIndex();
        const unsigned int* ptIndex = pairPreviewIndex.first;
        size_t szIndex = pairPreviewIndex.second;

        m_glView->addPreviewData(ptLines, szLines);
        m_glView->addPreviewIndex(ptIndex, szIndex);

        //for (size_t i = 0; i < szLines; i += 6)
        //{
        //    MRender::ColorPoint pt{ *(ptLines + i), *(ptLines + i + 1),  *(ptLines + i + 2),
        //        *(ptLines + i + 3),*(ptLines + i + 4),*(ptLines + i + 5) };

        //    m_glView->addLinesPoint(pt);
        //}
    }

    if (1)
    {
        auto imgPreviewData = m_scene->getDrawData()->getImageData();

        //float* ptLines = pairPreviewData.first;
        //size_t szLines = pairPreviewData.second;

        //auto pairPreviewIndex = m_scene->getDrawData()->getPreviewsIndex();
        //const unsigned int* ptIndex = pairPreviewIndex.first;
        //size_t szIndex = pairPreviewIndex.second;

        //m_glView->addPreviewData(ptLines, szLines);
        //m_glView->addPreviewIndex(ptIndex, szIndex);

        //for (size_t i = 0; i < szLines; i += 6)
        //{
        //    MRender::ColorPoint pt{ *(ptLines + i), *(ptLines + i + 1),  *(ptLines + i + 2),
        //        *(ptLines + i + 3),*(ptLines + i + 4),*(ptLines + i + 5) };

        //    m_glView->addLinesPoint(pt);
        //}
    }
    m_glView->update();
}

void ViewWrapper::updateScene()
{
    m_glView->clearLinePoints();

    auto rootGroup = m_scene->getRootGroup();
    if (rootGroup)
    {
        for (size_t i = 0; i < rootGroup->getChildrenCount(); ++i)
        {
            auto ent = rootGroup->getChild(i);
            if (ent && ent->getType() == MEngine::EntType::LINE)
            {
                auto line = static_cast<MEngine::Line*>(ent);

                Ut::Vec2 ptS, ptE;
                line->getPoints(ptS, ptE);

                MRender::ColorPoint pt1{ static_cast<float>(ptS.x()), static_cast<float>(ptS.y()), 0.0f, 1.0f, 0.0f, 0.0f };
                MRender::ColorPoint pt2{ static_cast<float>(ptE.x()), static_cast<float>(ptE.y()), 0.0f, 1.0f, 0.0f, 0.0f };

                m_glView->addLinePoint(pt1);
                m_glView->addLinePoint(pt2);
            }
        }
    }

    m_glView->update();
}

void ViewWrapper::setOperation(int nType)
{
    m_optManager->set(nType);
}

bool ViewWrapper::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == m_glView)
    {
        // 处理鼠标按下事件
        if (event->type() == QEvent::MouseButtonPress)
        {
            m_optManager->mousePressEvent(static_cast<QMouseEvent*>(event));
            return true;
        }
        else if (event->type() == QEvent::Paint)
        {
            return false;
        }
        else if (event->type() == QEvent::MouseButtonDblClick)
        {
            m_optManager->mouseDoubleClickEvent(static_cast<QMouseEvent*>(event));
            return true;
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            m_optManager->mouseReleaseEvent(static_cast<QMouseEvent*>(event));
            return true;
        }
        else if (event->type() == QEvent::MouseMove)
        {
            m_optManager->mouseMoveEvent(static_cast<QMouseEvent*>(event));
            this->mouseMoveEvent(static_cast<QMouseEvent*>(event));
            return false;
        }
        else if (event->type() == QEvent::KeyPress)
        {
            m_optManager->keyPressEvent(static_cast<QKeyEvent*>(event));
        }
        else if (event->type() == QEvent::KeyRelease)
        {
            m_optManager->keyReleaseEvent(static_cast<QKeyEvent*>(event));
            return true;
        }
        else if (event->type() == QEvent::Wheel)
        {
            m_optManager->wheelEvent(static_cast<QWheelEvent*>(event));
            return true;
        }
        else if (event->type() == QEvent::FocusIn)
        {
            //m_optManager->focusInEvent(static_cast<QFocusEvent*>(event));
            return true;
        }
        else if (event->type() == QEvent::FocusOut)
        {
            //m_optManager->focusOutEvent(static_cast<QFocusEvent*>(event));
            return true;
        }
        else if (event->type() == QEvent::Enter)
        {
            //m_optManager->enterEvent(event);
            return true;
        }
        else if (event->type() == QEvent::Leave) // 鼠标离开窗口区域
        {
            //m_optManager->leaveEvent(event);
            return true;
        }
    }

    // 对于未处理的事件，调用基类的eventFilter方法
    return QObject::eventFilter(obj, event);
}

void ViewWrapper::resizeEvent(QResizeEvent* event)
{
    //m_optManager->resizeEvent(event);
    //updateRender();

    auto sz = m_glView->size();
    m_scene->setView(sz.width(), sz.height());

    auto& mat = m_scene->getViewMatrix();
    m_glView->setViewMatrix(mat);
}

void ViewWrapper::mousePressEvent(QMouseEvent* event)
{
    //m_optManager->mousePressEvent(event);

    QWidget::mousePressEvent(event);
}

void ViewWrapper::mouseReleaseEvent(QMouseEvent* event)
{
    //m_optManager->mouseReleaseEvent(event);

    QWidget::mouseReleaseEvent(event);
}

void ViewWrapper::wheelEvent(QWheelEvent* event)
{
    m_optManager->wheelEvent(event);

    QWidget::wheelEvent(event);
}

void ViewWrapper::mouseMoveEvent(QMouseEvent* event)
{
    QPoint curPos = event->pos();
    Ut::Vec2d world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

    m_optManager->mouseMoveEvent(event);

    sigCoordChanged(world.x(), world.y());

    QWidget::mouseMoveEvent(event);
}

void ViewWrapper::keyPressEvent(QKeyEvent* event)
{
    m_optManager->keyPressEvent(event);

    if (event->key() == Qt::Key_F5)
    {
        updateRender();
    }

    QWidget::keyPressEvent(event);
}

void ViewWrapper::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
}