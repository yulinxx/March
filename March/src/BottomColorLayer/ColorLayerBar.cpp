#include "ColorLayerBar.h"
#include <QAction>
#include <QIcon>
#include <QLayout>
#include "def.h"

#include "../Widgets/TipWidget.h"
#include <QSignalMapper>
#include <QToolBar>
#include <QPushButton>
#include <QVBoxLayout>

// 定义常用颜色列表
const QList<QColor> colorList = {
    Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan,
    Qt::magenta, Qt::black, Qt::white, Qt::gray, Qt::darkRed,
    Qt::darkGreen, Qt::darkBlue, Qt::darkYellow, Qt::darkCyan,
    Qt::darkMagenta, Qt::lightGray, Qt::darkGray, QColor(255, 165, 0) };

ColorLayerBar::ColorLayerBar(QWidget* parent) : QDockWidget(parent)
{
    initUI();
    this->adjustSize();
    // 设置大小策略
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void ColorLayerBar::initUI()
{
    setFeatures(features() & ~QDockWidget::DockWidgetClosable);

    m_toolbar = new QToolBar(this);
    m_toolbar->setIconSize(QSize(32, 32));
    m_toolbar->layout()->setContentsMargins(0, 0, 0, 0);

    setAllowedAreas(Qt::AllDockWidgetAreas);
    setWidget(m_toolbar);

    // 创建信号映射器
    QSignalMapper* signalMapper = new QSignalMapper(this);

    for (const QColor& color : colorList)
    {
        // 添加间隔
        QWidget* spacer = new QWidget(this);
        spacer->setFixedWidth(10);
        m_toolbar->addWidget(spacer);

        QPushButton* button = new QPushButton(this);
        button->setStyleSheet(QString("background-color: %1;").arg(color.name()));
        button->setFixedSize(30, 30);

        connect(button, &QPushButton::clicked, signalMapper,
            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

        signalMapper->setMapping(button, color.name());

        m_toolbar->addWidget(button);
    }

    // 将信号映射器的映射信号连接到自定义槽函数
    connect(signalMapper, &QSignalMapper::mappedString,
        this, &ColorLayerBar::slotColorBtnClicked);

    connect(this, &QDockWidget::dockLocationChanged, this, &ColorLayerBar::slotDockPosChanged);
}

void ColorLayerBar::slotDockPosChanged(Qt::DockWidgetArea area)
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

void ColorLayerBar::slotColorBtnClicked(const QString& color)
{
    emit sigColorLayerSelected(color);
    TipWidget::instance()->showMessage(QString("颜色: %1").arg(color));
}