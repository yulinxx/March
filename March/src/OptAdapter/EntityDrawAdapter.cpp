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

    m_view->setOperation(n);
    return;
}