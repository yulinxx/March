#include "EntityDrawAdapter.h"
#include "Logger.h"
#include "MainWindow.h"
#include "Widgets/TipWidget.h"
#include "def.h"

#include "Entity/Line.h"
#include "Scene/Scene.h"
#include "Command/AddEntityCmd.h"
#include "Command/CommandManager.h"

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

    switch (n)
    {
    case static_cast<int>(DrawType::Point):
    {
        drawLine();
    }
    break;
    case static_cast<int>(DrawType::Line):
    {
        //for (int i = 0; i < 10000; i++)   // 内存泄露测试
        drawLine();
    }
    break;
    case static_cast<int>(DrawType::Polyline):
        break;
    case static_cast<int>(DrawType::Polygon):
        break;
    case static_cast<int>(DrawType::Circle):
        break;
    case static_cast<int>(DrawType::Ellipse):
        break;
    case static_cast<int>(DrawType::Arc):
        break;
    case static_cast<int>(DrawType::Spline):
        break;
    case static_cast<int>(DrawType::Text):
        break;
    case static_cast<int>(DrawType::Image):
        break;
    default:
        break;
    }

    size_t nEntSz = m_view->getScene()->getRootGroup()->getChildrenCount();

    m_mainWnd->getStatusBar()->slotSetItemsInfo(nEntSz);
    m_mainWnd->updateScene();
}