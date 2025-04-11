#include "LayerAdapter.h"
#include "MainWindow.h"
#include "BottomColorLayer/ColorLayerBar.h"

LayerAdapter::LayerAdapter(MainWindow* parent) : QObject(parent), m_mainWnd(parent)
{
    assert(parent);

    m_mainWnd = parent;

    auto colorLayerBar = parent->getColorLayerBar();
    connect(colorLayerBar, &ColorLayerBar::sigSelColorLayer, this, &LayerAdapter::slotSelLayer);

}

LayerAdapter::~LayerAdapter()
{
}

void LayerAdapter::slotSelLayer(const unsigned int color)
{

    // 解析 RGBA
    unsigned char r = (color >> 16) & 0xFF; // 红
    unsigned char g = (color >> 8) & 0xFF;  // 绿
    unsigned char b = color & 0xFF;         // 蓝
    unsigned char a = (color >> 24) & 0xFF; // 透明度

    qDebug() << "Selected Color:" << Qt::hex << color
        << "R:" << r << "G:" << g << "B:" << b << "A:" << a;

    //if (m_colorLayerBar) 
    {
        // 示例：调用 ColorLayerBar 的某个方法
        // m_colorLayerBar->createLayer(param);
        //emit sigStatusMsgChanged("Layer created successfully");

        m_mainWnd->getView()->getScene()->setLayer(color);
        //m_mainWnd->getView()->getScene()->setLayer(r, g, b, a);
        emit sigStatusMsgChanged("Layer created successfully");
    }
}