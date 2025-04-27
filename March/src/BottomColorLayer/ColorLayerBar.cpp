#include "ColorLayerBar.h"
#include <QToolBar>
#include <QLayout>
#include <QPushButton>
#include <QSignalMapper>

#include "Widgets/TipWidget.h"

// 定义常用颜色列表
const QList<QColor> colorList = {
    Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan,
    Qt::magenta, Qt::black, Qt::white, Qt::gray, Qt::darkRed,
    Qt::darkGreen, Qt::darkBlue, Qt::darkYellow, Qt::darkCyan,
    Qt::darkMagenta, Qt::lightGray, Qt::darkGray, QColor(255, 165, 0)
};

ColorLayerBar::ColorLayerBar(QWidget* parent) : QDockWidget(parent)
{
    initUI();
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

    QSignalMapper* signalMapper = new QSignalMapper(this);
    for (const QColor& color : colorList)
    {
        QWidget* spacer = new QWidget(m_toolbar);
        spacer->setFixedWidth(10);
        m_toolbar->addWidget(spacer);

        QPushButton* button = new QPushButton(m_toolbar);
        button->setStyleSheet(QString("background-color: %1;").arg(color.name()));
        button->setFixedSize(30, 30);
        button->setToolTip(color.name());

        //connect(button, &QPushButton::clicked, signalMapper, &QSignalMapper::map);

        connect(button, &QPushButton::clicked, signalMapper,
            static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

        signalMapper->setMapping(button, color.name());
        m_toolbar->addWidget(button);
    }

    connect(signalMapper, &QSignalMapper::mappedString, this, &ColorLayerBar::slotColorBtnClicked);
    connect(this, &QDockWidget::dockLocationChanged, this, &ColorLayerBar::slotDockPosChanged);
}

void ColorLayerBar::slotDockPosChanged(Qt::DockWidgetArea area)
{
    m_toolbar->setOrientation(area == Qt::TopDockWidgetArea || area == Qt::BottomDockWidgetArea
        ? Qt::Horizontal : Qt::Vertical);
}

void ColorLayerBar::slotColorBtnClicked(const QString& color)
{
    //emit sigSelColorLayer(color);

    QColor selectedColor(color);
    unsigned int nRGBA = selectedColor.rgba(); // 转换为 0xAARRGGBB
    emit sigSelColorLayer(nRGBA);

    TipWidget::instance()->showMessage(QString("颜色: %1").arg(color));
}