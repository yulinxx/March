#include "MainWindow.h"
#include <QFile>
#include <QStyleFactory>
#include <QMdiSubWindow>

#include <QStatusBar>
#include <QDockWidget>
#include <QLayout>
#include <QApplication>

#include "Logger.h"
#include "Widgets/TipWidget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    initUI();
    initData();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initData()
{
    TipWidget::instance(this);

    MLog::Logger::LogInfo("Welcome");
    TipWidget::instance()->showMessage("Welcome");

    m_entityAdapter = new EntityDrawAdapter(this);
    m_fileAdapter = new FileAdapter(this);
    m_msgAdapter = new MsgAdapter(this);
    m_layerAdapter = new LayerAdapter(this);
}

void MainWindow::initUI()
{
    setMinimumSize(QSize(800, 600));

    setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AnimatedDocks);

    m_menuBar = new MenuBar(this);
    setMenuBar(m_menuBar);

    m_mainToolBar = new InfoToolBar(this);
    addToolBar(Qt::TopToolBarArea, m_mainToolBar);

    m_drawToolBar = new DrawToolBar(this);
    addDockWidget(Qt::LeftDockWidgetArea, m_drawToolBar);

    m_hardInfoDock = new HardInfoDock(this);
    addDockWidget(Qt::RightDockWidgetArea, m_hardInfoDock);

    m_colorLayer = new ColorLayerBar(this);
    addDockWidget(Qt::BottomDockWidgetArea, m_colorLayer);
    m_statusBar = new StatusInfoBar(this);
    // m_statusBar->showMessage(tr("Hello,March V1.0"));

    setStatusBar(m_statusBar);

    // 创建 QTabWidget 并设置为中心部件
    m_tabView = new QTabWidget(this);
    setCentralWidget(m_tabView);

    connect(m_menuBar, &MenuBar::sigShowDrawToolBar, this, [this]() { m_drawToolBar->show(); });
    connect(m_menuBar, &MenuBar::sigShowHardInfoDock, this, [this]() { m_hardInfoDock->show(); });

    if (1)
    {
        QFile styleFile(":/theme/MacOS.qss");

        if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString styleSheet = QLatin1String(styleFile.readAll());
            qApp->setStyleSheet(styleSheet);
            styleFile.close();
        }
        else
        {
            MLog::Logger::LogError("Failed to open style file: " + styleFile.fileName().toStdString());
        }

        qApp->setStyle(QStyleFactory::create("Fusion"));
    }
    resize(1400, 1200);

    createNewView();
}

void MainWindow::updateScene()
{
    getView()->updateScene();
}

void MainWindow::createNewView()
{
    // TOOD: 新建的文档需重新绑定信号槽
    ViewWrapper* viewWrapper = new ViewWrapper();
    if (!m_tabView)
    {
        delete viewWrapper;
        return;
    }

    int index = m_tabView->addTab(viewWrapper, tr("View %1").arg(m_tabView->count() + 1));
    m_tabView->setCurrentIndex(index);

    if (m_msgAdapter)
        m_msgAdapter->reInit();
}

MenuBar* MainWindow::getMenuBar() const
{
    return m_menuBar;
}

InfoToolBar* MainWindow::getMainToolBar() const
{
    return m_mainToolBar;
}

DrawToolBar* MainWindow::getDrawToolBar() const
{
    return m_drawToolBar;
}

ColorLayerBar* MainWindow::getColorLayerBar() const
{
    return m_colorLayer;
}

HardInfoDock* MainWindow::getHardInfoDock() const
{
    return m_hardInfoDock;
}

StatusInfoBar* MainWindow::getStatusBar() const
{
    return m_statusBar;
}

QTabWidget* MainWindow::getViewTab() const
{
    return m_tabView;
}

ViewWrapper* MainWindow::getView() const
{
    return qobject_cast<ViewWrapper*>(m_tabView->currentWidget());
}

QList<ViewWrapper*> MainWindow::getAllViews() const
{
    QList<ViewWrapper*> views;
    if (!m_tabView) return views;

    for (int i = 0; i < m_tabView->count(); ++i)
    {
        if (auto view = qobject_cast<ViewWrapper*>(m_tabView->widget(i)))
        {
            views.append(view);
        }
    }

    return views;
}