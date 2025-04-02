#include "MsgAdapter.h"
#include "MainWindow.h"

MsgAdapter::MsgAdapter(MainWindow* parent) : QObject(parent)
{
    m_mainWnd = parent;
    reInit();
}

void MsgAdapter::reInit()
{
    if (!m_mainWnd)
        return;

    auto views = m_mainWnd->getAllViews();
    auto statusBar = m_mainWnd->getStatusBar();

    for (auto view : views)
    {
        connect(view, &ViewWrapper::sigCoordChanged, statusBar,
            &StatusInfoBar::slotSetCoordInfo, Qt::UniqueConnection);
    }
}