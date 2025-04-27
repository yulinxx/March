#include "EntityDrawAdapter.h"

#include "Logger.h"
#include "MainWindow.h"
#include "Widgets/TipWidget.h"

#include <cstdlib>
#include <ctime>
#include <memory>

EntityDrawAdapter::EntityDrawAdapter(MainWindow* parent)
    : QObject(parent)
{
    assert(parent);
    m_mainWnd = parent;

    // std::srand(std::time(nullptr)); // 初始化随机数种子

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