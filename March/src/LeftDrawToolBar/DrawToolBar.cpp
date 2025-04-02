#include "DrawToolBar.h"
#include <QAction>
#include <QIcon>
#include <QLayout>
#include "def.h"

#include "../Widgets/TipWidget.h"

DrawToolBar::DrawToolBar(QWidget* parent) : QDockWidget(parent)
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

    m_actSelect = new QAction(QIcon("://icons/draw-select.png"), tr("Select"), this);
    m_actDrawPoint = new QAction(QIcon("://icons/draw-point.png"), tr("Point"), this);
    m_actDrawLine = new QAction(QIcon("://icons/draw-line.png"), tr("Line"), this);
    m_actDrawPline = new QAction(QIcon("://icons/draw-pline.png"), tr("Polyline"), this);
    m_actDrawCircle = new QAction(QIcon("://icons/draw-circle.png"), tr("Circle"), this);
    m_actDrawText = new QAction(QIcon("://icons/draw-text.png"), tr("Text"), this);
    m_actDrawArc = new QAction(QIcon("://icons/draw-elliptic-arc.png"), tr("Arc"), this);
    m_actDrawPolygon = new QAction(QIcon("://icons/draw-polygon.png"), tr("Polygon"), this);
    m_actDrawImage = new QAction(QIcon("://icons/draw-image.png"), tr("Image"), this);

    connect(m_actSelect, &QAction::triggered, this, [this]() {
        emit sigEntityOpration(static_cast<int>((0)));
        });
    connect(m_actDrawPoint, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>(DrawType::Point));
        });
    connect(m_actDrawLine, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Line)));
        });
    connect(m_actDrawPline, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Polyline)));
        });
    connect(m_actDrawCircle, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Circle)));
        });
    connect(m_actDrawText, &QAction::triggered, this, [this]() {
        emit sigCreateEntity(static_cast<int>((DrawType::Text)));
        });
    connect(m_actDrawArc, &QAction::triggered, this, [this]() {
        TipWidget::instance()->showMessage(tr("Arc"));
        });
    connect(m_actDrawPolygon, &QAction::triggered, this, [this]() {
        TipWidget::instance()->showMessage(tr("Polygon"));
        });
    connect(m_actDrawImage, &QAction::triggered, this, &DrawToolBar::slotDrawImage);

    m_toolbar->addAction(m_actSelect);
    m_toolbar->addSeparator();
    m_toolbar->addAction(m_actDrawPoint);
    m_toolbar->addAction(m_actDrawLine);
    m_toolbar->addAction(m_actDrawPline);
    m_toolbar->addAction(m_actDrawCircle);
    m_toolbar->addAction(m_actDrawText);
    m_toolbar->addAction(m_actDrawArc);
    m_toolbar->addAction(m_actDrawPolygon);
    m_toolbar->addSeparator();
    m_toolbar->addAction(m_actDrawImage);
    m_toolbar->setOrientation(Qt::Vertical);

    connect(this, &QDockWidget::dockLocationChanged, this, &DrawToolBar::slotDockPosChanged);
}

// 绘图工具槽函数
void DrawToolBar::slotSelect()
{
    emit sigEntityOpration(static_cast<int>((0)));
}

void DrawToolBar::slotDrawPoint()
{
    emit sigCreateEntity(static_cast<int>(DrawType::Point));
}

void DrawToolBar::slotDrawLine()
{
    emit sigCreateEntity(static_cast<int>((DrawType::Line)));
}

void DrawToolBar::slotDrawPline()
{
    emit sigCreateEntity(static_cast<int>((DrawType::Polyline)));
}

void DrawToolBar::slotDrawCircle()
{
    emit sigCreateEntity(static_cast<int>((DrawType::Circle)));
}

void DrawToolBar::slotDrawText()
{
    emit sigCreateEntity(static_cast<int>((DrawType::Text)));
}

void DrawToolBar::slotDrawArc()
{
    TipWidget::instance()->showMessage(tr("Arc"));
}

void DrawToolBar::slotDrawPolygon()
{
    TipWidget::instance()->showMessage(tr("Polygon"));
}

// 长文本测试用
void DrawToolBar::slotDrawImage()
{
    TipWidget::instance()->showMessage(
        tr("ImageImageImageImageImageImageImageImageImageImageImageImageImageImage\
        ImageImageImageImageImageImageImageImageImageImageImageImageImageImageImageImageImageImage"));
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