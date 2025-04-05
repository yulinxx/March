#include "DrawToolBar.h"

#include <QIcon>
#include <QLayout>
#include "def.h"

#include "Widgets/TipWidget.h"

DrawToolBar::DrawToolBar(QWidget* parent)
    : QDockWidget(parent)
{
    initUI();
    this->adjustSize();
}

void DrawToolBar::initUI()
{
    setFeatures(features() & ~QDockWidget::DockWidgetClosable);

    m_toolbar = new QToolBar(this);
    // m_toolbar->setMovable(false);
    m_toolbar->setIconSize(QSize(32, 32));
    m_toolbar->layout()->setContentsMargins(0, 0, 0, 0);

    setAllowedAreas(Qt::AllDockWidgetAreas);
    setWidget(m_toolbar);

    // 使用有序map管理操作类型与action的对应关系
    const std::map<int, std::pair<QString, QString>> mapActionCfg{
        {static_cast<int>(DrawType::Select),    {tr("Select"),    "://icons/draw-select.png"}},
        {static_cast<int>(DrawType::Point),     {tr("Point"),     "://icons/draw-point.png"}},
        {static_cast<int>(DrawType::Line),      {tr("Line"),      "://icons/draw-line.png"}},
        {static_cast<int>(DrawType::Polyline),  {tr("Polyline"),  "://icons/draw-pline.png"}},
        {static_cast<int>(DrawType::Polygon),   {tr("Polygon"),   "://icons/draw-polygon.png"}},
        {static_cast<int>(DrawType::Rectangle), {tr("Rectangle"), "://icons/draw-rectangle.png"}},
        {static_cast<int>(DrawType::Arc),       {tr("Arc"),       "://icons/draw-arc.png"}},
        {static_cast<int>(DrawType::Circle),    {tr("Circle"),    "://icons/draw-circle.png"}},
        {static_cast<int>(DrawType::Ellipse),   {tr("Ellipse"),   "://icons/draw-ellipse.png"}},
        {static_cast<int>(DrawType::Text),      {tr("Text"),      "://icons/draw-text.png"}},
        {static_cast<int>(DrawType::Image),     {tr("Image"),     "://icons/draw-image.png"}}
    };

    // 批量创建并配置action
    for (const auto& [type, config] : mapActionCfg)
    {
        QAction* action = new QAction(QIcon(config.second), config.first, this);
        action->setData(static_cast<int>(type));
        m_mapActions[type] = action;
    }

    auto handleAction = [this]() {
        if (auto action = qobject_cast<QAction*>(sender()))
        {
            DrawType type = static_cast<DrawType>(action->data().toInt());
            if (type == DrawType::Select)
            {
                emit sigEntityOpration(static_cast<int>(type));
            }
            else
            {
                emit sigCreateEntity(static_cast<int>(type));
            }
        }
        };

    // 批量连接信号
    for (auto& [_, action] : m_mapActions)
    {
        connect(action, &QAction::triggered, this, handleAction);
    }

    m_toolbar->addAction(m_mapActions[static_cast<int>(DrawType::Select)]);

    m_toolbar->addSeparator();
    for (int i = 1; i < 7; ++i)
    {
        m_toolbar->addAction(m_mapActions[i]);
    }
    m_toolbar->addSeparator();
    m_toolbar->addAction(m_mapActions[static_cast<int>(DrawType::Image)]);

    connect(this, &QDockWidget::dockLocationChanged, this, &DrawToolBar::slotDockPosChanged);
}

void DrawToolBar::slotDockPosChanged(Qt::DockWidgetArea area)
{
    if (area == Qt::TopDockWidgetArea || area == Qt::BottomDockWidgetArea)
    {
        m_toolbar->setOrientation(Qt::Horizontal);
    }
    else
    {
        m_toolbar->setOrientation(Qt::Vertical);
    }
}