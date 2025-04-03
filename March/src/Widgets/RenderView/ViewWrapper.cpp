#include "ViewWrapper.h"

#include <algorithm>
#include <random>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDateTime>
#include <QApplication>
#include <QDebug>

#include "Entity/Line.h"

ViewWrapper::ViewWrapper(QWidget* parent) : QWidget(parent)
{
    m_scene = new MEngine::Scene();

    //m_scene->setRenderVidget(m_glView);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_glView = new MRender::MarchView(this);
    layout->addWidget(m_glView);
    m_glView->installEventFilter(this);

    setLayout(layout);


    m_curOpt = std::make_shared<OptBase>(m_scene);
    m_curOpt->setGLView(m_glView);

    // 启用鼠标跟踪
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

ViewWrapper::~ViewWrapper()
{
}

void ViewWrapper::resetView()
{
    m_curOpt->resetView();
    //auto sz = m_glView->size();
    //m_scene->setView(sz.width(), sz.height());

    //auto mat = m_scene->getViewMatrix();
    //m_glView->clearLinePoints();
    //m_glView->setViewMatrix(mat);
    //m_glView->update();
}

const std::vector<MRender::ColorPoint>& ViewWrapper::getLinePoints() const
{
    return m_glView->getLinePoints();
}

//float ViewWrapper::getScale() const
//{
//    return 1.0;
//    //return m_glView->getScale();
//}

//QVector2D ViewWrapper::getTranslation() const
//{
//    return m_glView->getTranslation();
//}

MRender::MarchView* ViewWrapper::getGlView() const
{
    return m_glView;
}

MEngine::Scene* ViewWrapper::getScene()
{
    return m_scene;
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
            if (ent && ent->m_eType == MEngine::ETYPE::LINE)
            {
                auto line = static_cast<MEngine::Line*>(ent);

                auto ptS = line->m_basePt;
                auto ptE = line->m_secPoint;

                MRender::ColorPoint pt1{ static_cast<float>(ptS.x()), static_cast<float>(ptS.y()), 0.0f, 1.0f, 0.0f, 0.0f };
                MRender::ColorPoint pt2{ static_cast<float>(ptE.x()), static_cast<float>(ptE.y()), 0.0f, 1.0f, 0.0f, 0.0f };

                m_glView->addLinePoint(pt1);
                m_glView->addLinePoint(pt2);
            }
        }
    }

    m_glView->update();
}

void ViewWrapper::setOperation(std::shared_ptr<OptBase> operation)
{
    m_curOpt = operation;
}

bool ViewWrapper::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == m_glView)
    {
        // 处理鼠标按下事件
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
            {
            }
            else if (mouseEvent->button() == Qt::RightButton)
            {
            }
            return false;
        }
        else if (event->type() == QEvent::Paint)
        {
            return false;
        }
        else if (event->type() == QEvent::MouseButtonDblClick)
        {
            return false;
        }
        // 处理鼠标释放事件
        //else if (event->type() == QEvent::MouseButtonRelease)
        //{
        //    qDebug() << "Mouse button released on MarchView";
        //    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        //    if (mouseEvent->button() == Qt::LeftButton)
        //    {
        //    }
        //    return true;
        //}
        // 处理鼠标移动事件
        //else if (event->type() == QEvent::MouseMove)
        //{
        //    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        //    return true;
        //}
        // 处理键盘按下事件
        else if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "Key pressed:" << keyEvent->key();
            return true;
        }
    }

    // 对于未处理的事件，调用基类的eventFilter方法
    return QObject::eventFilter(obj, event);
}

void ViewWrapper::resizeEvent(QResizeEvent* event)
{
    m_curOpt->resizeEvent(event);

    //auto sz = m_glView->size();
    //m_scene->setView(sz.width(), sz.height());

    //auto mat = m_scene->getViewMatrix();
    //m_glView->setViewMatrix(mat);
}

void ViewWrapper::mousePressEvent(QMouseEvent* event)
{
    m_curOpt->mousePressEvent(event);
    //if (event->button() == Qt::MiddleButton)
    //{
    //    m_lastPanPos = event->pos();
    //    m_bPanning = true;

    //    if (1)
    //    {
    //        qint64 curTime = QDateTime::currentMSecsSinceEpoch();
    //        if (curTime - m_lastMiddleClickTime < QApplication::doubleClickInterval()
    //            && (event->pos() - m_lastMiddlePos).manhattanLength() < 5)
    //        {
    //            resetView();
    //            return;
    //        }
    //        m_lastMiddleClickTime = curTime;
    //        m_lastMiddlePos = event->pos();
    //        m_lastPos = event->pos();
    //    }
    //}
    //else if (event->button() == Qt::LeftButton)
    //{
    //    // 记录选择起始点
    //    m_selectStart = m_scene->screenToWorld({ event->pos().x(), event->pos().y() });
    //    m_selectEnd = m_selectStart;
    //    m_bSelecting = true;

    //    // 清除之前的选择
    //    //m_scene->clearSelection();
    //    //m_glView->update();

    //    {
    //        std::random_device rd;
    //        std::mt19937 gen(rd());
    //        std::uniform_real_distribution<float> disColor(0.0f, 1.0f);
    //        float r = disColor(gen);
    //        float g = disColor(gen);
    //        float b = disColor(gen);

    //        auto world = m_scene->screenToWorld({ event->pos().x(), event->pos().y() });

    //        m_glView->addLinePoint({ float(world.x()), float(world.y()), 0.0f, r, g, b });
    //        m_glView->update();
    //    }
    //}
    //else if (event->button() == Qt::RightButton)
    //{
    //    std::random_device rd;
    //    std::mt19937 gen(rd());
    //    std::uniform_real_distribution<float> disColor(0.0f, 1.0f);

    //    Ut::Vec2d sz = m_scene->getViewSize();
    //    float aspect = float(sz.x() / sz.y());

    //    Ut::Vec2d center = m_scene->getViewCenter();

    //    float dScale = m_scene->getViewScale();

    //    std::uniform_real_distribution<float> disX(center.x() - (sz.x() * 0.5), center.x() + (sz.x() * 0.5));
    //    std::uniform_real_distribution<float> disY(center.y() - (sz.y() * 0.5), center.y() + (sz.y() * 0.5));

    //    for (int i = 0; i < 100; ++i)
    //    {
    //        float randomX = disX(gen);
    //        float randomY = disY(gen);
    //        float r = disColor(gen);
    //        float g = disColor(gen);
    //        float b = disColor(gen);
    //        m_glView->addLinePoint({ randomX, randomY, 0.0f, r, g, b });
    //    }

    //    m_glView->update();
    //}
    //else if (event->button() == Qt::MiddleButton)
    //{
    //    m_lastPos = event->pos();
    //}

    QWidget::mousePressEvent(event);
}

void ViewWrapper::mouseReleaseEvent(QMouseEvent* event)
{
    m_curOpt->mouseReleaseEvent(event);

    //if (event->button() == Qt::LeftButton && m_bSelecting)
    //{
    //    // 计算选择区域
    //    Ut::Vec2d minPt(
    //        std::min(m_selectStart.x(), m_selectEnd.x()),
    //        std::min(m_selectStart.y(), m_selectEnd.y())
    //    );

    //    Ut::Vec2d maxPt(
    //        std::max(m_selectStart.x(), m_selectEnd.x()),
    //        std::max(m_selectStart.y(), m_selectEnd.y())
    //    );

    //    // 判断选择方向
    //    bool bCrossSel = (m_selectEnd.x() < m_selectStart.x());

    //    // 执行选择
    //    if (bCrossSel)
    //    {
    //        qDebug() << "Cross selection";
    //        //m_scene->selectByCross(minPt, maxPt); // 交选
    //    }
    //    else
    //    {
    //        qDebug() << "Window selection";
    //        //m_scene->selectByWindow(minPt, maxPt); // 窗选
    //    }

    //    m_bSelecting = false;
    //    m_glView->update();
    //}
    //else if (event->button() == Qt::MiddleButton)
    //{
    //    m_bPanning = false;
    //}
    QWidget::mouseReleaseEvent(event);
}

void ViewWrapper::wheelEvent(QWheelEvent* event)
{
    m_curOpt->wheelEvent(event);
    //if (0)
    //{
    //    //QPoint mousePos = event->position().toPoint();
    //    //float currentScale = getScale();
    //    //QVector2D curTrans = getTranslation();
    //    //float delta = event->angleDelta().y() > 0 ? 1.1f : 0.9f;
    //    ////QPointF worldMousePos = screenToWorld(mousePos);
    //    //auto worldMousePos = m_scene->screenToWorld({ mousePos.x(), mousePos.y() });
    //    //float newScale = currentScale * delta;

    //    //// 计算新的平移量，以保持鼠标位置在缩放后仍然是视图中心
    //    //QVector2D newTranslation = curTrans + QVector2D(
    //    //    (worldMousePos.x() - curTrans.x()) / currentScale -
    //    //    (worldMousePos.x() - curTrans.x()) / newScale,
    //    //    (worldMousePos.y() - curTrans.y()) / currentScale -
    //    //    (worldMousePos.y() - curTrans.y()) / newScale
    //    //) * newScale; // 此处乘以newScale是为了调整平移量到新的缩放级别

    //    //// 更新视图的缩放比例和平移量
    //    ////m_glView->setScale(newScale);
    //    //m_glView->setTranslation(newTranslation);
    //    //m_glView->update();

    //    QWidget::wheelEvent(event);
    //}
    //else // 以视图为中心缩放
    //{
    //    QPoint curPos = event->pos();
    //    auto world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

    //    float delta = event->angleDelta().y() > 0 ? 1.1f : 0.9f;

    //    m_scene->zoomAt(Ut::Vec2{ world.x(), world.y() }, delta);
    //    //m_scene->setZoom(delta);

    //    Ut::Mat3 matView = m_scene->getViewMatrix();
    //    m_glView->setViewMatrix(matView);

    //    m_glView->update();

    //    sigCoordChanged(world.x(), world.y());

    //    QWidget::wheelEvent(event);
    //}

    QWidget::wheelEvent(event);
}

void ViewWrapper::mouseMoveEvent(QMouseEvent* event)
{
    QPoint curPos = event->pos();
    auto world = m_scene->screenToWorld({ curPos.x(), curPos.y() });

    m_curOpt->mouseMoveEvent(event);

    //if (m_bSelecting && (event->buttons() & Qt::LeftButton))
    //{
    //    m_selectEnd = world;
    //}
    //if (event->buttons() & Qt::MiddleButton)
    //{
    //    if (m_bPanning)
    //    {
    //        auto posA = m_scene->screenToWorld({ m_lastPanPos.x(), m_lastPanPos.y() });
    //        auto dir = world - posA;

    //        m_scene->pan(dir);

    //        auto mat = m_scene->getViewMatrix();
    //        m_glView->setViewMatrix(mat);

    //        m_lastPanPos = curPos;

    //        update();
    //    }
    //}

    sigCoordChanged(world.x(), world.y());

    QWidget::mouseMoveEvent(event);
}

void ViewWrapper::keyPressEvent(QKeyEvent* event)
{
    m_curOpt->keyPressEvent(event);
    //if (event->key() == Qt::Key_Escape)
    //{
    //    m_bPanning = false;
    //}
    //if (event->key() == Qt::Key_Delete)
    //{
    //    m_glView->clearLinePoints();
    //    m_glView->update();
    //}
    //else
    //{
    //    QWidget::keyPressEvent(event);
    //}

    QWidget::keyPressEvent(event);
}

void ViewWrapper::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
}