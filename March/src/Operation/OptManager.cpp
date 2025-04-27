#include "OptManager.h"
#include <QMouseEvent>
#include <QKeyEvent>

#include "Operation/OptBase.h"
#include "Operation/Select/OptSelect.h"
#include "Operation/Draw/OptDrawPoint.h"
#include "Operation/Draw/OptDrawLine.h"
#include "Operation/Draw/OptDrawPolyLine.h"
#include "Operation/Draw/OptDrawRectangle.h"
#include "Operation/Draw/OptDrawPolygon.h"
#include "Operation/Draw/OptDrawArc.h"
#include "Operation/Draw/OptDrawCircle.h"
#include "Operation/Draw/OptDrawEllipse.h"
#include "Operation/Draw/OptDrawSpline.h"
#include "Operation/Draw/OptDrawCubicBezier.h"
#include "Operation/Draw/OptDrawText.h"
#include "Operation/Draw/OptDrawImage.h"

#include "MLog/Logger.h"

OptManager::OptManager(ViewWrapper* viewWidget,
    MEngine::Scene* scene,
    MRender::MarchView* glView
)
{
    if (!viewWidget || !scene || !glView)
    {
        std::abort();
        return;
    }

    m_viewWrap = viewWidget;
    m_scene = scene;
    m_glView = glView;

    m_selectOpt = std::make_shared<OptSelect>(m_scene); // 初始化默认操作
    m_selectOpt->setViewWidget(m_viewWrap);
    m_selectOpt->setGLView(m_glView);

    m_curOpt = m_selectOpt;
}

void OptManager::set(int nType)
{
    // 判断是否是同一个操作，是则不处理
    if (static_cast<int>(m_curOpt->getDrawType()) == nType)
        return;

    m_curOpt->exit();

    MLog::Logger::LogInfo("Current Operation: " + std::to_string(nType));

    switch (nType)
    {
    case static_cast<int>(DrawType::Select):
        m_curOpt = std::make_shared<OptSelect>(m_scene);
        break;
    case static_cast<int>(DrawType::Point):
        m_curOpt = std::make_shared<OptDrawPoint>(m_scene);
        break;
    case static_cast<int>(DrawType::Line):
        m_curOpt = std::make_shared<OptDrawLine>(m_scene);
        break;
    case static_cast<int>(DrawType::Polyline):
        m_curOpt = std::make_shared<OptDrawPolyLine>(m_scene);
        break;
    case static_cast<int>(DrawType::Rectangle):
        m_curOpt = std::make_shared<OptDrawRectangle>(m_scene);
        break;
    case static_cast<int>(DrawType::Polygon):
        m_curOpt = std::make_shared<OptDrawPolygon>(m_scene);
        break;
    case static_cast<int>(DrawType::Arc):
        m_curOpt = std::make_shared<OptDrawArc>(m_scene);
        break;
    case static_cast<int>(DrawType::Circle):
        m_curOpt = std::make_shared<OptDrawCircle>(m_scene);
        break;
    case static_cast<int>(DrawType::Ellipse):
        m_curOpt = std::make_shared<OptDrawEllipse>(m_scene);
        break;
    case static_cast<int>(DrawType::Spline):
        m_curOpt = std::make_shared<OptDrawSpline>(m_scene);
        break;
    case static_cast<int>(DrawType::Bezier):
        m_curOpt = std::make_shared<OptDrawCubicBezier>(m_scene);
        break;
    case static_cast<int>(DrawType::Text):
        m_curOpt = std::make_shared<OptDrawText>(m_scene);
        break;
    case static_cast<int>(DrawType::Image):
        m_curOpt = std::make_shared<OptDrawImage>(m_scene);
        break;
    default:
        m_curOpt = m_selectOpt; // 默认操作
        break;
    }


    m_curOpt->setViewWidget(m_viewWrap);
    m_curOpt->setGLView(m_glView);

    m_curOpt->enter();
}

void OptManager::setDefaultOpt()
{
    m_curOpt = m_selectOpt; // 需要提前初始化m_selectOpt
}

// 事件转发实现
void OptManager::mousePressEvent(QMouseEvent* event)
{
    if (m_curOpt)
        m_curOpt->mousePressEvent(event);
}

void OptManager::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_curOpt)
        m_curOpt->mouseReleaseEvent(event);
}

void OptManager::mouseMoveEvent(QMouseEvent* event)
{
    if (m_curOpt)
        m_curOpt->mouseMoveEvent(event);
}

void OptManager::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (m_curOpt)
        m_curOpt->mouseDoubleClickEvent(event);
}

void OptManager::wheelEvent(QWheelEvent* event)
{
    if (m_curOpt)
        m_curOpt->wheelEvent(event);
}

void OptManager::keyPressEvent(QKeyEvent* event)
{
    if (m_curOpt)
        m_curOpt->keyPressEvent(event);
}

void OptManager::keyReleaseEvent(QKeyEvent* event)
{
    if (m_curOpt)
        m_curOpt->keyReleaseEvent(event);
}

void OptManager::resizeEvent(QResizeEvent* event)
{
    if (m_curOpt)
        m_curOpt->resizeEvent(event);
}

void OptManager::enterEvent(QEnterEvent* event)
{
    if (m_curOpt)
        m_curOpt->enterEvent(event);
}

void OptManager::leaveEvent(QEvent* event)
{
    if (m_curOpt)
        m_curOpt->leaveEvent(event);
}