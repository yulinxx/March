#include "EntityDrawAdapter.h"

#include "Logger.h"
#include "MainWindow.h"
#include "Widgets/TipWidget.h"
#include "def.h"

#include "Entity/Line.h"
#include "Scene/Scene.h"
#include "Command/AddEntityCmd.h"
#include "Command/CommandManager.h"

#include "Operation/Draw/OptDrawPoint.h"
#include "Operation/Draw/OptDrawLine.h"
#include "Operation/Draw/OptDrawPolygon.h"
#include "Operation/Draw/OptDrawCircle.h"
#include "Operation/Draw/OptDrawArc.h"
#include "Operation/Draw/OptDrawEllipse.h"
#include "Operation/Draw/OptDrawSpline.h"
//#include "Operation/Draw/OptDrawPolyline.h"
#include "Operation/Draw/OptDrawText.h"
#include "Operation/Draw/OptDrawImage.h"

#include <cstdlib>
#include <ctime>
#include <memory>

EntityDrawAdapter::EntityDrawAdapter(MainWindow* parent)
    : QObject(parent)
{
    assert(parent);
    m_mainWnd = parent;

    std::srand(std::time(nullptr)); // 初始化随机数种子

    DrawToolBar* drawTool = parent->getDrawToolBar();
    connect(drawTool, &DrawToolBar::sigCreateEntity, this, &EntityDrawAdapter::slotCreateEntity);

    MenuBar* menuBar = parent->getMenuBar();
    connect(menuBar, &MenuBar::sigCreateEntity, this, &EntityDrawAdapter::slotCreateEntity);

    m_view = parent->getView();
}

void EntityDrawAdapter::slotCreateEntity(int n)
{
    TipWidget::instance()->showMessage(QString("DrawType: %1").arg(n));

    if (0)
    {
        auto getPt = []() {
            return static_cast<float>(std::rand() % 1000);
            };

        static int i = 0;

        auto drawLine = [&]() {
            MEngine::Line* line = new MEngine::Line();
            // auto line = std::make_shared<MEngine::Line>();

            line->m_basePt = Ut::Vec2d(getPt(), getPt());
            line->m_secPoint = Ut::Vec2d(getPt(), getPt());
            line->m_nId = i;
            i++;

            auto s = m_view->getScene();
            auto addCmd = std::make_unique<MEngine::AddEntityCmd>(s->getRootGroup(), line);
            s->execute(std::move(addCmd));
            };
    }

    switch (n)
    {
    case static_cast<int>(DrawType::Point):
    {
        auto optDrawPoint = std::make_shared<OptDrawPoint>(m_view->getScene());
        m_view->setOperation(optDrawPoint);
        break;
    }
    case static_cast<int>(DrawType::Line):
    {
        //for (int i = 0; i < 10000; i++)   // 内存泄露测试
        //drawLine();
        auto optDrawLine = std::make_shared<OptDrawLine>(m_view->getScene());
        m_view->setOperation(optDrawLine);
        break;
    }
    //case static_cast<int>(DrawType::Polyline):
    //{
    //    auto optDrawPolyline = std::make_shared<OptDrawPolyline>(m_view->getScene());
    //    m_view->setOperation(optDrawPolyline);
    //    break;
    //}
    case static_cast<int>(DrawType::Polygon):
    {
        auto optDrawPolygon = std::make_shared<OptDrawPolygon>(m_view->getScene());
        m_view->setOperation(optDrawPolygon);
        break;
    }
    case static_cast<int>(DrawType::Circle):
    {
        auto optDrawCircle = std::make_shared<OptDrawCircle>(m_view->getScene());
        m_view->setOperation(optDrawCircle);
        break;
    }
    case static_cast<int>(DrawType::Ellipse):
    {
        auto optDrawEllipse = std::make_shared<OptDrawEllipse>(m_view->getScene());
        m_view->setOperation(optDrawEllipse);
        break;
    }
    case static_cast<int>(DrawType::Arc):
    {
        auto optDrawArc = std::make_shared<OptDrawArc>(m_view->getScene());
        m_view->setOperation(optDrawArc);
        break;
    }
    case static_cast<int>(DrawType::Spline):
    {
        auto optDrawSpline = std::make_shared<OptDrawSpline>(m_view->getScene());
        m_view->setOperation(optDrawSpline);
        break;
    }
    case static_cast<int>(DrawType::Text):
    {
        auto optDrawText = std::make_shared<OptDrawText>(m_view->getScene());
        m_view->setOperation(optDrawText);
        break;
    }
    case static_cast<int>(DrawType::Image):
    {
        auto optDrawImage = std::make_shared<OptDrawImage>(m_view->getScene());
        m_view->setOperation(optDrawImage);
        break;
    }
    default:
        break;
    }

    size_t nEntSz = m_view->getScene()->getRootGroup()->getChildrenCount();

    m_mainWnd->getStatusBar()->slotSetItemsInfo(nEntSz);
    m_mainWnd->updateScene();
}